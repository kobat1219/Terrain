#pragma once
#include	<d3d11.h>
#include	<wrl/client.h>

// ComPtrはスマポのこと。
using Microsoft::WRL::ComPtr;

/// <summary>
/// DXグラフィッククラス
/// </summary>
class DirectXGraphics {
private:
	DirectXGraphics() {}	//空実装
	ComPtr<ID3D11Device>			m_lpDevice;					// DIRECT3DDEVICE11デバイス
	ComPtr<ID3D11DeviceContext>		m_lpImmediateContext;		// DIRECT3DDEVICE11デバイスコンテキスト
	ComPtr<IDXGISwapChain>			m_lpSwapChain;				// スワップチェイン

	ComPtr<ID3D11RenderTargetView>	m_lpRenderTargetView;		// レンダーターゲットビュー
	ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;		// Ｚバッファ、ステンシルバッファ
	ComPtr<ID3D11DepthStencilState>	m_depthStencilState;		// Ｚバッファ、ステンシルステート
	ComPtr<ID3D11DepthStencilView>	m_depthStencilView;			// Ｚバッファ、ステンシルビュー
	ComPtr<ID3D11RasterizerState>	m_rasterSolidState;				// ラスターステータス
	ComPtr<ID3D11RasterizerState>	m_rasterWireState;				// ラスターステータス

	D3D_DRIVER_TYPE					m_DriverType;				// ドライバタイプ
	D3D_FEATURE_LEVEL				m_FeatureLevel;				// 機能レベル

	ComPtr<ID3D11BlendState>		m_alphaEnableBlendingState;		// アルファブレンドステート（有効）
	ComPtr<ID3D11BlendState>		m_alphaDisableBlendingState;	// アルファブレンドステート（無効）

	ComPtr<ID3D11SamplerState>		m_samplerstate;					// サンプラーステート

	int								m_Width = 0;				// バックバッファＸサイズ
	int								m_Height = 0;				// バックバッファＹサイズ
public:
	
	// コピーコンストラクタをオーバーライド。コピーが作られないように。
	DirectXGraphics(const DirectXGraphics&) = delete;
	DirectXGraphics& operator=(const DirectXGraphics&) = delete;
	DirectXGraphics(DirectXGraphics&&) = delete;
	DirectXGraphics& operator=(DirectXGraphics&&) = delete;

	// デストラクタ
	~DirectXGraphics() {
		// 解放処理
		Exit();
	}

	// インスタンス取得
	static DirectXGraphics* GetInstance() {
		static DirectXGraphics instance;
		return &instance;
	}

	/// <summary>
	/// DirectX Grpaphics の初期化処理
	/// </summary>
	/// <param name="hWnd">ウインドウハンドル値</param>
	/// <param name="Width">ウインドウサイズ（幅）</param>
	/// <param name="Height">ウインドウサイズ（高さ）</param>
	/// <param name="fullscreen">フルスクリーン（false window  true fullscreen )</param>
	/// <returns>
	/// false : 失敗　
	/// true  : 成功
	/// </returns>
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool fullscreen);

	/// <summary>
	/// DirectX Grpaphics の終了処理
	/// </summary>
	void Exit();

	// デバイスGET
	ID3D11Device*	GetDXDevice() const {
		return m_lpDevice.Get();
	}

	// イミディエイトデバイスGET。イミディエイトは即時という意味。
	// なのでこのイミディエイトに伝えると即時にGPUに発行される。
	// これは、デバイスコンテキストと同じ。
	// メインスレッドのみで使える。マルチスレッドの場合は、メインに伝えないといけない。
	ID3D11DeviceContext* GetImmediateContext() const {
		return m_lpImmediateContext.Get();
	}

	// SWAPチェインGET
	IDXGISwapChain* GetSwapChain()const {
		return m_lpSwapChain.Get();
	}

	// レンダリングターゲットGET
	ID3D11RenderTargetView* GetRenderTargetView() const {
		return m_lpRenderTargetView.Get();
	}

	// depthstencil view
	ID3D11DepthStencilView* GetDepthStencilView() const {
		return m_depthStencilView.Get();
	}

	// ビューポートの高さを取得する
	int GetViewPortHeight() const {
		return m_Height;
	}

	// ビューポートの幅を取得する
	int GetViewPortWidth() const {
		return m_Width;
	}

	// アルファブレンド有効化
	void TurnOnAlphaBlending();

	// アルファブレンド無効化
	void TurnOffAlphaBlending();

	// Zバッファ無効化
	void TurnOffZbuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// ターゲット
			rtvtable,								// ビューテーブル
			nullptr									// 深度バッファなし
		);
	}

	// Zバッファ有効化
	void TurnOnZBuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// ターゲット
			rtvtable,								// ビューテーブル
			m_depthStencilView.Get()				// 深度バッファなし
		);
	}

	void SetSampler(ID3D11DeviceContext* device)
	{
		device->PSSetSamplers(0, 1, m_samplerstate.GetAddressOf());
	}

	void TurnSolid()
	{
		//  set the rasterizer state
		m_lpImmediateContext->RSSetState(m_rasterSolidState.Get());
	}
	void TurnWire()
	{
		//  set the rasterizer state
		m_lpImmediateContext->RSSetState(m_rasterWireState.Get());
	}
};
