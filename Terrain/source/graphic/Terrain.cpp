#include "Terrain.h"
#include "../core/Macro.h"

#include <fstream>
#include <mutex>
#include <thread>

void GpuTerrain::Init()
{
	CreateIndexAndVertexBuffer();
	
	CreateShader();

	CreateCSUseSampler();

	CreatePexTexture();

	NewMap();
	//Load("assets/terrain/data/heightmap.TIF");

	CreateHeightmapCS();

	CreateCrossPointCS();

	CreateEditCS();

	// テクスチャのパッチごとの係数を得る
	CalHeighmapCS();
}

void GpuTerrain::NewMap()
{
	m_HeightMapBuffer.clear();

	for (size_t i = 0; i < m_heightMapDivSize*m_heightMapDivSize; i++)
	{
		m_HeightMapBuffer.emplace_back(0.0f);
	}

	D3D11_TEXTURE2D_DESC descuav;
	ZeroMemory(&descuav, sizeof(D3D11_TEXTURE2D_DESC));
	descuav.Width = m_heightMapDivSize;
	descuav.Height = m_heightMapDivSize;
	descuav.MipLevels = 1;
	descuav.ArraySize = 1;
	descuav.Format = DXGI_FORMAT_R32_FLOAT;
	descuav.CPUAccessFlags = D3D11_CPU_ACCESS_READ| D3D11_CPU_ACCESS_WRITE;
	descuav.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	descuav.MiscFlags = 0;			// その他の設定なし
	descuav.SampleDesc.Count = 1;		// マルチサンプリング数
	descuav.SampleDesc.Quality = 0;		// マルチサンプルクオリティ
	descuav.Usage = D3D11_USAGE_DEFAULT;    // デフォルト使用法

	D3D11_TEXTURE2D_DESC descsrv;
	ZeroMemory(&descsrv, sizeof(D3D11_TEXTURE2D_DESC));
	descsrv.Width = m_heightMapDivSize;
	descsrv.Height = m_heightMapDivSize;
	descsrv.MipLevels = 1;
	descsrv.ArraySize = 1;
	descsrv.Format = DXGI_FORMAT_R32_FLOAT;
	descsrv.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	descsrv.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	descsrv.MiscFlags = 0;			// その他の設定なし
	descsrv.SampleDesc.Count = 1;		// マルチサンプリング数
	descsrv.SampleDesc.Quality = 0;		// マルチサンプルクオリティ
	descsrv.Usage = D3D11_USAGE_DEFAULT;    // デフォルト使用法

	auto device = GetDX11Device();
	// 2Dテクスチャを生成
	HRESULT hr = device->CreateTexture2D(
		&descuav,// 作成する2Dテクスチャの設定
		nullptr,// 
		&m_pHeightMapT2DUABuf);// 作成したテクスチャを受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "CreateTexture error", "Error", MB_OK);

	hr = device->CreateTexture2D(
		&descsrv,// 作成する2Dテクスチャの設定
		nullptr,// 
		&m_pHeightMapT2DSRBuf);// 作成したテクスチャを受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "CreateTexture error", "Error", MB_OK);


	//hr = GetDX11DeviceContext()->Map(m_pHeightMapT2DBuf.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	//if (SUCCEEDED(hr)) {
	//	memcpy_s(pData.pData, pData.DepthPitch, (void*)(m_HeightMapBuffer.data()), sizeof(float) * m_heightMapDivSize*m_heightMapDivSize);
	//	GetDX11DeviceContext()->Unmap(m_pHeightMapT2DBuf.Get(), 0);
	//}

	//シェーダ リソース ビューの作成する為の情報をセット
	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = DXGI_FORMAT_R32_FLOAT; 	// フォーマット

	srDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	srDesc.Texture2D.MostDetailedMip = 0;		// 最初のミップマップ レベル
	srDesc.Texture2D.MipLevels = -1;			// すべてのミップマップ レベル

	// シェーダ リソース ビューの生成
	hr = device->CreateShaderResourceView(
		m_pHeightMapT2DSRBuf.Get(),	// アクセスするテクスチャ リソース
		&srDesc,		// シェーダ リソース ビューの設定
		&m_pHeightMapT2DBufSRV);	// ＳＲＶ受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "SRV error", "Error", MB_OK);

	// アンオーダー アクセス ビューの生成
	hr = device->CreateUnorderedAccessView(m_pHeightMapT2DUABuf.Get(), nullptr, m_pHeightMapT2DBufUAV.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateUnorderedAccessView error", "Error", MB_OK);
	}

	descuav.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	descsrv.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	srDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; 	// フォーマット

	// 2Dテクスチャを生成
	hr = device->CreateTexture2D(
		&descuav,// 作成する2Dテクスチャの設定
		nullptr,// 
		&m_pNormalAndTexT2DUABuf);// 作成したテクスチャを受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "CreateTexture error", "Error", MB_OK);

	hr = device->CreateTexture2D(
		&descsrv,// 作成する2Dテクスチャの設定
		nullptr,// 
		&m_pNormalAndTexT2DSRBuf);// 作成したテクスチャを受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "CreateTexture error", "Error", MB_OK);


	//hr = GetDX11DeviceContext()->Map(m_pHeightMapT2DBuf.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	//if (SUCCEEDED(hr)) {
	//	memcpy_s(pData.pData, pData.DepthPitch, (void*)(m_HeightMapBuffer.data()), sizeof(float) * m_heightMapDivSize*m_heightMapDivSize);
	//	GetDX11DeviceContext()->Unmap(m_pHeightMapT2DBuf.Get(), 0);
	//}

	// シェーダ リソース ビューの生成
	hr = device->CreateShaderResourceView(
		m_pNormalAndTexT2DSRBuf.Get(),	// アクセスするテクスチャ リソース
		&srDesc,		// シェーダ リソース ビューの設定
		&m_pNormalAndTexT2DBufSRV);	// ＳＲＶ受け取る変数
	if (FAILED(hr))
		MessageBox(nullptr, "SRV error", "Error", MB_OK);

	// アンオーダー アクセス ビューの生成
	hr = device->CreateUnorderedAccessView(m_pNormalAndTexT2DUABuf.Get(), nullptr, m_pNormalAndTexT2DBufUAV.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateUnorderedAccessView error", "Error", MB_OK);
	}
}

void GpuTerrain::Draw(const MyEngine::float3& _camerapos)
{
	UpdateFactor(_camerapos);
	auto device = GetDX11DeviceContext();
	device->DSSetSamplers(0, 1, m_samplerstate.GetAddressOf());
	// 頂点バッファをセットする
	unsigned int stride = sizeof(Vertex);
	unsigned  offset = 0;
	device->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	device->DSSetShaderResources(0, 1, m_pHeightMapT2DBufSRV.GetAddressOf());
	device->DSSetShaderResources(1, 1, m_pNormalAndTexT2DBufSRV.GetAddressOf());
	device->HSSetShaderResources(10, 1, m_factorStructBufferSRV.GetAddressOf());
	//device->PSSetShaderResources(0, 1, &m_pHeightMapT2DBufSRV);
	//device->HSSetShaderResources(0, 1, &m_pHeightMapT2DBufSRV);

	//device->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);			// インデックスバッファをセット
	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);		// トポロジーをセット（旧プリミティブタイプ）
	device->IASetInputLayout(m_inputLayout.Get());					// 頂点レイアウトセット

	device->VSSetShader(m_vertexShader.Get(), nullptr, 0);			// 頂点シェーダーをセット
	device->PSSetShader(m_pixelShader.Get(), nullptr, 0);			// ピクセルシェーダーをセット
	device->HSSetShader(m_hullShader.Get(), nullptr, 0);			// ピクセルシェーダーをセット
	device->DSSetShader(m_domainShader.Get(), nullptr, 0);			// ピクセルシェーダーをセット

	device->Draw(
		static_cast<unsigned int>(m_vertex.size()),		// 描画するインデックス数
		//0,									// 最初のインデックスバッファの位置
		0);									// 頂点バッファの最初から使う

	device->HSSetShader(nullptr, nullptr, 0);			// りセット
	device->DSSetShader(nullptr, nullptr, 0);			// りセット
}

void GpuTerrain::SetMaxLength(const float& _length)
{
	m_maxLength = _length;
}

float GpuTerrain::GetMaxLength()
{
	return m_maxLength;
}

bool GpuTerrain::CreateIndexAndVertexBuffer()
{
	m_vertex.clear();
	for (unsigned int z = 0; z < m_div; z++)
	{
		for (unsigned int x = 0; x < m_div; x++)
		{
			Vertex v;
			printf("--\n");
			v.Pos = { -((m_div/2) * m_divsize) + x * m_divsize, 0, -((m_div / 2) * m_divsize) + (z+1) * m_divsize };
			v.Uv = { (float)x / (float)m_div, (float)(z+1) / (float)m_div};
			printf("%f,%f\n", v.Uv.x, v.Uv.y);
			m_vertex.emplace_back(v);
			
			v.Pos = { -((m_div / 2) * m_divsize) + (x+1) * m_divsize, 0, -((m_div / 2) * m_divsize) + (z+1) * m_divsize };
			v.Uv = { (float)(x+1) / (float)m_div, (float)(z+1) / (float)m_div};
			printf("%f,%f\n", v.Uv.x, v.Uv.y);
			m_vertex.emplace_back(v);
			
			v.Pos = { -((m_div / 2) * m_divsize) + (x + 1) * m_divsize, 0, -((m_div / 2) * m_divsize) + z * m_divsize };
			v.Uv = { (float)(x+1) / (float)m_div, (float)z / (float)m_div };
			printf("%f,%f\n", v.Uv.x, v.Uv.y);
			m_vertex.emplace_back(v);
			
			v.Pos = { -((m_div / 2) * m_divsize) + x * m_divsize, 0, -((m_div / 2) * m_divsize) + z * m_divsize };
			v.Uv = { (float)x / (float)m_div, (float)z / (float)m_div };
			printf("%f,%f\n", v.Uv.x, v.Uv.y);
			m_vertex.emplace_back(v);

		}
	}

	// 頂点バッファ作成
	bool sts = CreateVertexBuffer(
		GetDX11Device(),								// デバイスオブジェクト
		sizeof(Vertex),						// １頂点当たりバイト数
		(unsigned int)m_vertex.size(),					// 頂点数
		m_vertex.data(),					// 頂点データ格納メモリ先頭アドレス
		m_vertexBuffer.GetAddressOf());	// 頂点バッファ

	if (!sts) {
		MessageBox(NULL, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}
	
	m_factor.resize((size_t)m_div * (size_t)m_div);

	sts = CreateStructuredBuffer(
		DirectXGraphics::GetInstance()->GetDXDevice(),
		sizeof(DivFactor),
		(unsigned int)m_factor.size(),
		m_factor.data(),
		&m_factorStructBuffer);

	if (!sts) {
		MessageBox(nullptr, "CreateStructuredBuffer error", "error", MB_OK);
		return false;
	}

	sts = CreateShaderResourceView(
		DirectXGraphics::GetInstance()->GetDXDevice(),
		m_factorStructBuffer.Get(),
		&m_factorStructBufferSRV
	);

	if (!sts) {
		MessageBox(nullptr, "CreateShaderResourceView error", "error", MB_OK);
		return false;
	}

	return true;
}

bool GpuTerrain::CreateHeightmapCS()
{
	auto device = GetDX11Device();
	bool sts = CreateComputeShader(
		device,
		"shader/csheightfactercal.hlsl",
		"CS_Main",
		"cs_5_0",
		&m_heightComputeShader);

	if (!sts) {
		MessageBox(nullptr, "CreateComputeShader error", "error", MB_OK);
		return false;
	}
	// コンピュートシェーダーへの入力時に使用するシェーダーリソースビューを作成する
	sts = CreateStructuredBuffer(
		device,
		sizeof(Anser),
		16 * 16,
		&getdata[0],
		&m_ansstrcuturedBuf);
	if (sts == false)
	{
		MessageBox(nullptr, "CPSHADERERROR", "ERROR", MB_OK);
		return false;
	}

	// コンピュートシェーダーからの出力時に使用するアンオーダードアクセスビューを作成する
	sts = CreateUnOrderAccessView(device, m_ansstrcuturedBuf.Get(), &m_ansstrcuturedUAV);
	if (sts == false)
	{
		MessageBox(nullptr, "CPSHADERERROR", "ERROR", MB_OK);
		return false;
	}


	return true;
}

bool GpuTerrain::CreateCrossPointCS()
{
	auto device = GetDX11Device();
	bool sts = CreateComputeShader(
		device,
		"shader/csterrainray.hlsl",
		"CS_Main",
		"cs_5_0",
		&m_crossComputeShader);

	if (!sts) {
		MessageBox(nullptr, "CreateComputeShader error", "error", MB_OK);
		return false;
	}
	// コンピュートシェーダーへの入力時に使用するシェーダーリソースビューを作成する
	sts = CreateStructuredBuffer(
		device,
		sizeof(Anser),
		ARRAYSIZE(crossdata),
		&crossdata[0],
		&m_crossstrcuturedBuf);
	if (sts == false)
	{
		MessageBox(nullptr, "CPSHADERERROR", "ERROR", MB_OK);
		return false;
	}

	// コンピュートシェーダーからの出力時に使用するアンオーダードアクセスビューを作成する
	sts = CreateUnOrderAccessView(device, m_crossstrcuturedBuf.Get(), &m_crossstrcuturedUAV);
	if (sts == false)
	{
		MessageBox(nullptr, "CPSHADERERROR", "ERROR", MB_OK);
		return false;
	}

	// コンスタントバッファ作成
	sts = CreateConstantBuffer(
		device,			// デバイス
		sizeof(ConstantMapProperty),	// サイズ
		&m_constantMapPropertyBuf);			// コンスタントバッファ２
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(constant buffer world) error", "Error", MB_OK);
		return false;
	}


	return true;
}

bool GpuTerrain::CreateEditCS()
{
	auto device = GetDX11Device();
	bool sts = CreateComputeShader(
		device,
		"shader/csterrainupdate.hlsl",
		"CS_Main",
		"cs_5_0",
		&m_terrainEditComputeShader);

	if (!sts) {
		MessageBox(nullptr, "CreateComputeShader error", "error", MB_OK);
		return false;
	}

	// コンスタントバッファ作成
	sts = CreateConstantBuffer(
		device,			// デバイス
		sizeof(ConstantEditProperty),	// サイズ
		&m_constantEditPropertyBuf);			// コンスタントバッファ２
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(constant buffer world) error", "Error", MB_OK);
		return false;
	}


	return true;
}

bool GpuTerrain::CreateShader()
{
	auto dev = GetDX11Device();

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	bool sts = CreateVertexShader(
		dev,
		"shader/vsterrain.hlsl",
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_vertexShader,
		&m_inputLayout
	);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	sts = CreateHullShader(
		dev,
		"shader/hsterrain.hlsl",
		"HS",
		"hs_5_0",
		&m_hullShader
	);
	if (!sts) {
		MessageBox(nullptr, "CreateShader error", "error", MB_OK);
		return false;
	}
	sts = CreateDomainShader(
		dev,
		"shader/dsterrain.hlsl",
		"DS",
		"ds_5_0",
		&m_domainShader
	);
	if (!sts) {
		MessageBox(nullptr, "CreateShader error", "error", MB_OK);
		return false;
	}
	sts = CreatePixelShader(
		dev,
		"shader/psterrain.hlsl",
		"main",
		"ps_5_0",
		&m_pixelShader
	);

	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	

	return true;
}

bool GpuTerrain::CreateCSUseSampler()
{
	// サンプラーステート設定
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	//smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	//smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	//smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	//smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	//smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	//	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//	smpDesc.MinLOD = 0;
	//	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// サンプラーステート生成
	HRESULT hr = GetDX11Device()->CreateSamplerState(&smpDesc, &m_samplerstate);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool GpuTerrain::CreatePexTexture()
{
	auto device = GetDX11Device();
	auto devicecon = GetDX11DeviceContext();
	ComPtr<ID3D11Resource> tmp;
	CreateSRVfromWICFile("assets/pentex/trpen_nomal.png", device, devicecon, tmp.GetAddressOf(), m_pentexsrv.GetAddressOf());
	m_pentex["nomal"].Swap(tmp);
	CreateSRVfromWICFile("assets/pentex/trpen_nomal_set.png", device, devicecon, tmp.GetAddressOf(), m_pentexsrv.GetAddressOf());
	m_pentex["nomal_set"].Swap(tmp);
	CreateSRVfromWICFile("assets/pentex/trpen_star.png", device, devicecon, tmp.GetAddressOf(), m_pentexsrv.GetAddressOf());
	m_pentex["star"].Swap(tmp);
	CreateSRVfromWICFile("assets/pentex/trpen_uzu.png", device, devicecon, tmp.GetAddressOf(), m_pentexsrv.GetAddressOf());
	m_pentex["uzu"].Swap(tmp);
	CreateSRVfromWICFile("assets/pentex/trpen_hart.png", device, devicecon, tmp.GetAddressOf(), m_pentexsrv.GetAddressOf());
	m_pentex["hart"].Swap(tmp);
	return false;
}

void GpuTerrain::UpdateFactor(const MyEngine::float3& _camerapos)
{
	using namespace MyEngine;
	UINT cnt = 0;
	std::vector<std::vector<float>> tmpans;
	
	// まず一時的な分割数を計算する。
	for (unsigned int z = 0; z < m_div; z++)
	{
		std::vector<float> tmpbuf;
		for (unsigned int x = 0; x < m_div; x++)
		{
			float3 vertpos;
			vertpos.x= m_vertex[cnt * 4].Pos.x;
			vertpos.y= m_vertex[cnt * 4].Pos.y;
			vertpos.z= m_vertex[cnt * 4].Pos.z;

			float distance = float3::Length(_camerapos - vertpos);
			CLAMP_VALUE(distance, m_minLength, m_maxLength);
			float gr = (distance - m_minLength) / (m_maxLength - m_minLength);
			// 一時的な分割数を入れる

			distance = 1;

			if (gr < 0.2f)
			{
				distance = 64;
			}
			else if (gr < 0.3f)
			{
				distance = 32;
			}
			else if (gr < 0.5f)
			{
				distance = 16;
			}
			else if (gr < 0.7f)
			{
				distance = 8;
			}
			else if (gr < 0.8f)
			{
				distance = 4;
			}
			else if (gr < 0.9f)
			{
				distance = 2;
			}
			float sn = 0;

			if (getdata[cnt].factor.w!=0)
			{
				sn= (1.0f / (float)m_heightMapDivSize) / getdata[cnt].factor.w; // sin値
			}
			else if(getdata[cnt].factor.y== getdata[cnt].factor.z)
			{
				distance /= 2;
			}

			// 係数を一時配列に入れる
			tmpbuf.emplace_back(distance);
			cnt++;
		}
		tmpans.emplace_back(tmpbuf);
	}

	cnt = 0;

	for (int z = 0; z < m_div; z++)
	{
		for (int x = 0; x < m_div; x++)
		{
			
			float divbase = tmpans[z][x];
			m_factor[cnt].inside[0] =
			m_factor[cnt].factor[0] = 
			m_factor[cnt].factor[1] = 
			m_factor[cnt].factor[2] = 
			m_factor[cnt].factor[3] = divbase;
			
			if (z - 1 >= 0)
			{
				if (tmpans[z - 1][x] < divbase)
				{
					m_factor[cnt].factor[3] = tmpans[z - 1][x];
				}
			}
			if (x + 1 < m_div)
			{
				if (tmpans[z][x + 1] < divbase)
				{
					m_factor[cnt].factor[2] = tmpans[z][x + 1];
				}
			}
			if (z + 1 < m_div)
			{
				if (tmpans[z + 1][x] < divbase)
				{
					m_factor[cnt].factor[1] = tmpans[z + 1][x];
				}
			}
			if (x - 1 >= 0)
			{
				if (tmpans[z][x - 1] < divbase)
				{
					m_factor[cnt].factor[0] = tmpans[z][x - 1];
				}
			}
			cnt++;
		}
	}

	if (m_factor.size() == 0)
	{
		return;
	}

	// データのアップデート
	ID3D11DeviceContext* devicecontext = DirectXGraphics::GetInstance()->GetImmediateContext();
	devicecontext->UpdateSubresource(m_factorStructBuffer.Get(), 0, nullptr, m_factor.data(), 0, 0);

}

void GpuTerrain::UpdateEditConstantData(const ConstantEditProperty& _Data)
{
	m_constantEditProperty = _Data;
	auto devicecontext = GetDX11DeviceContext();
	devicecontext->UpdateSubresource(m_constantEditPropertyBuf.Get(), 0, nullptr, &m_constantEditProperty, 0, 0);
	devicecontext->CSSetConstantBuffers(11, 1, m_constantEditPropertyBuf.GetAddressOf());
}

// アンオーダードアクセスビューのバッファの内容を CPU から読み込み可能なバッファへコピーする
ID3D11Buffer* CreateAndCopyToDebugBuf(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pD3DDeviceContext, ID3D11Buffer* pBuffer)
{
	ID3D11Buffer* debugbuf = NULL;

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	pBuffer->GetDesc(&BufferDesc);
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;  // CPU から読み込みできるように設定する
	BufferDesc.Usage = D3D11_USAGE_STAGING;             // GPU から CPU へのデータ転送 (コピー) をサポートするリソース
	BufferDesc.BindFlags = 0;
	BufferDesc.MiscFlags = 0;
	if (FAILED(pD3DDevice->CreateBuffer(&BufferDesc, NULL, &debugbuf)))
		goto EXIT;

	pD3DDeviceContext->CopyResource(debugbuf, pBuffer);

EXIT:
	return debugbuf;
}
// アンオーダードアクセスビューのバッファの内容を CPU から読み込み可能なバッファへコピーする
ID3D11Texture2D* CreateAndCopyToDebugBufTexture2D(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pD3DDeviceContext, ID3D11Texture2D* pBuffer)
{
	ID3D11Texture2D* debugbuf = NULL;

	D3D11_TEXTURE2D_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	pBuffer->GetDesc(&BufferDesc);
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;  // CPU から読み込みできるように設定する
	BufferDesc.Usage = D3D11_USAGE_STAGING;             // GPU から CPU へのデータ転送 (コピー) をサポートするリソース
	BufferDesc.BindFlags = 0;
	BufferDesc.MiscFlags = 0;
	if (FAILED(pD3DDevice->CreateTexture2D(&BufferDesc, NULL, &debugbuf)))
		goto EXIT;

	pD3DDeviceContext->CopyResource(debugbuf, pBuffer);

EXIT:
	return debugbuf;
}

void GpuTerrain::CalHeighmapCS()
{
	auto pD3DDeviceContext = GetDX11DeviceContext();

	pD3DDeviceContext->CSSetShader(m_heightComputeShader.Get(), NULL, 0);

	pD3DDeviceContext->CSSetSamplers(0,1,m_samplerstate.GetAddressOf());

	// シェーダーリソースビューをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetShaderResources(0, 1, m_pHeightMapT2DBufSRV.GetAddressOf());

	// アンオーダードアクセスビューをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, m_ansstrcuturedUAV.GetAddressOf(), NULL);

	// コンピュートシェーダーを実行する。
	pD3DDeviceContext->Dispatch((UINT)m_div, 1, 1);

	pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);

	ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
	pD3DDeviceContext->CSSetShaderResources(0, 2, ppSRVNULL);

	ID3D11Buffer* ppCBNULL[1] = { NULL };
	pD3DDeviceContext->CSSetConstantBuffers(0, 1, ppCBNULL);

	// アンオーダードアクセスビューのバッファの内容を CPU から読み込み可能なバッファへコピーする
	ID3D11Buffer* debugbuf = CreateAndCopyToDebugBuf(GetDX11Device(), pD3DDeviceContext, m_ansstrcuturedBuf.Get());
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	HRESULT hr = pD3DDeviceContext->Map(debugbuf, 0, D3D11_MAP_READ, 0, &MappedResource);
	if (SUCCEEDED(hr))
	{
		Anser* p = reinterpret_cast<Anser*>(MappedResource.pData);
		//memcpy_s(&getdata[0], 16 * 16, MappedResource.pData, sizeof(Anser) * 16 * 16);
		for (size_t i = 0; i < 16*16; i++)
		{

			getdata[i] = p[i];
			//printf("%f,", getdata[i].factor.y);
			//if (i%16==15)
			//{
			//	printf("\n");
			//}
		}
		pD3DDeviceContext->Unmap(debugbuf, 0);
	}

	SAFE_RELEASE(debugbuf);
}

void GpuTerrain::CalCrossPointCS()
{
	auto pD3DDeviceContext = GetDX11DeviceContext();

	pD3DDeviceContext->CSSetShader(m_crossComputeShader.Get(), NULL, 0);

	pD3DDeviceContext->CSSetSamplers(0, 1, m_samplerstate.GetAddressOf());

	// シェーダーリソースビューをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetShaderResources(0, 1, m_pHeightMapT2DBufSRV.GetAddressOf());

	// アンオーダードアクセスビューをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, m_crossstrcuturedUAV.GetAddressOf(), NULL);

	// コンピュートシェーダーを実行する。
	pD3DDeviceContext->Dispatch((UINT)m_div, 1, 1);

	pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);

	ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
	pD3DDeviceContext->CSSetShaderResources(0, 2, ppSRVNULL);

	ID3D11Buffer* ppCBNULL[1] = { NULL };
	pD3DDeviceContext->CSSetConstantBuffers(0, 1, ppCBNULL);

	// アンオーダードアクセスビューのバッファの内容を CPU から読み込み可能なバッファへコピーする
	ID3D11Buffer* debugbuf = CreateAndCopyToDebugBuf(GetDX11Device(), pD3DDeviceContext, m_crossstrcuturedBuf.Get());
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	HRESULT hr = pD3DDeviceContext->Map(debugbuf, 0, D3D11_MAP_READ, 0, &MappedResource);
	if (SUCCEEDED(hr))
	{
		Anser* p = reinterpret_cast<Anser*>(MappedResource.pData);
		for (size_t i = 0; i < 16 * 64 * 2; i++)
		{
			crossdata[i] = p[i];
			if (p[i].factor.x != 0 || p[i].factor.y != 0 || p[i].factor.z != 0)
			{
				printf("%f.%f,%f,%f", crossdata[i].factor.x, crossdata[i].factor.y, crossdata[i].factor.z, crossdata[i].factor.w );
			
				printf("\n");
			}
		
		}		
		printf("===\n");
		pD3DDeviceContext->Unmap(debugbuf, 0);
	}

	SAFE_RELEASE(debugbuf);
}

void GpuTerrain::CalEditCS()
{
	auto pD3DDeviceContext = GetDX11DeviceContext();

	pD3DDeviceContext->CSSetShader(m_terrainEditComputeShader.Get(), NULL, 0);

	pD3DDeviceContext->CSSetSamplers(0, 1, m_samplerstate.GetAddressOf());

	// SRVをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetShaderResources(0, 1, m_pentexsrv.GetAddressOf());
	// アンオーダードアクセスビューをコンピュートシェーダーに設定
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, m_pHeightMapT2DBufUAV.GetAddressOf(), NULL);
	pD3DDeviceContext->CSSetUnorderedAccessViews(1, 1, m_pNormalAndTexT2DBufUAV.GetAddressOf(), NULL);

	MyEngine::int2 pos;
	int loopsize = m_heightMapDivSize / m_div;
	pos.x = m_constantEditProperty.UVAndRangeAndCoef.x - m_constantEditProperty.UVAndRangeAndCoef.z;
	pos.y = m_constantEditProperty.UVAndRangeAndCoef.y - m_constantEditProperty.UVAndRangeAndCoef.z;

	int step = 0;
	if (pos.x% loopsize>=1)
	{
		step = 1;
	}
	pos.x = pos.x / loopsize + step;
	step = 0;
	if (pos.y % loopsize >= 1)
	{
		step = 1;
	}
	pos.y = pos.y / loopsize + step;


	MyEngine::int2 pos2;
	pos2.x = m_constantEditProperty.UVAndRangeAndCoef.x + m_constantEditProperty.UVAndRangeAndCoef.z;
	pos2.y = m_constantEditProperty.UVAndRangeAndCoef.y + m_constantEditProperty.UVAndRangeAndCoef.z;

	step = 0;
	if (pos2.x% loopsize>=1)
	{
		step = 1;
	}
	pos2.x = pos2.x / loopsize + step;
	step = 0;
	if (pos2.y % loopsize >= 1)
	{
		step = 1;
	}
	pos2.y = pos2.y / loopsize + step;

	// ペンサイズを計算しなければ
	UINT valx = pos2.x - pos.x + 1; 
	CLAMP_VALUE(valx, 1, 16);
	UINT valy = pos2.y - pos.y + 1; 
	CLAMP_VALUE(valy, 1, 16);
	// コンピュートシェーダーを実行する。
	pD3DDeviceContext->Dispatch(valx, valy, 1);

	//pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

	pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
	pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);
	pD3DDeviceContext->CSSetUnorderedAccessViews(1, 1, ppUAViewNULL, NULL);

	ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
	pD3DDeviceContext->CSSetShaderResources(0, 2, ppSRVNULL);

	ID3D11Buffer* ppCBNULL[1] = { NULL };
	pD3DDeviceContext->CSSetConstantBuffers(0, 1, ppCBNULL);

	// SRVにコピー
	pD3DDeviceContext->CopyResource(m_pHeightMapT2DSRBuf.Get(), m_pHeightMapT2DUABuf.Get());
	pD3DDeviceContext->CopyResource(m_pNormalAndTexT2DSRBuf.Get(), m_pNormalAndTexT2DUABuf.Get());
}

void GpuTerrain::SetPenSRV(std::string _str)
{
	auto devcon = GetDX11Device();
	if (m_pentex.count(_str)==0)
	{
		return;
	}
	devcon->CreateShaderResourceView(m_pentex[_str].Get(), nullptr, m_pentexsrv.GetAddressOf());
}
