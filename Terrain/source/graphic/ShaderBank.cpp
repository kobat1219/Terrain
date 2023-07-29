#include "ShaderBank.h"
#include "../directx/DirectXGraphics.h"
#include "Shader.h"

bool ShaderBank::SetPixelShader(
	std::string _pixelshaderpath,
	ID3D11PixelShader** _pixelShaderAnser)
{
    if (pixelshader.count(_pixelshaderpath))
    {
		*_pixelShaderAnser = pixelshader[_pixelshaderpath].Get();
		return true;
    }

    ComPtr<ID3D11PixelShader> _pixelshader;
    bool sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
		DirectXGraphics::GetInstance()->GetDXDevice(),		// デバイスオブジェクト
		_pixelshaderpath.c_str(),
		"main",
		"ps_5_0",
		&_pixelshader);

	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	pixelshader[_pixelshaderpath].Swap(_pixelshader);

	*_pixelShaderAnser = pixelshader[_pixelshaderpath].Get();

	return true;
}

bool ShaderBank::SetVertexShader(
	std::string _vertecshaderpath,
	D3D11_INPUT_ELEMENT_DESC _layout[],
	unsigned int _numElements,
	ID3D11VertexShader** _vertexShaderAnser,
	ID3D11InputLayout** _inputLayerAnser)
{
	if (vershader.count(_vertecshaderpath)&&inputlayout.count(_vertecshaderpath))
	{
		*_vertexShaderAnser = vershader[_vertecshaderpath].Get();
		*_inputLayerAnser = inputlayout[_vertecshaderpath].Get();
		return true;
	}

	ComPtr<ID3D11VertexShader> _vertexshader;
	ComPtr<ID3D11InputLayout> _inputlayer;

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	bool sts = CreateVertexShader(
		DirectXGraphics::GetInstance()->GetDXDevice(),
		_vertecshaderpath.c_str(),
		"main",
		"vs_5_0",
		_layout,
		_numElements,
		&_vertexshader,
		&_inputlayer);

	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	vershader[_vertecshaderpath].Swap(_vertexshader);
	inputlayout[_vertecshaderpath].Swap(_inputlayer);

	*_vertexShaderAnser = vershader[_vertecshaderpath].Get();
	*_inputLayerAnser = inputlayout[_vertecshaderpath].Get();

	return true;
}

ID3D11PixelShader* ShaderBank::GetPixelShader(const std::string& _path)
{
	if (pixelshader.count(_path))
	{
		return pixelshader[_path].Get();
	}
	return nullptr;
}

ID3D11VertexShader* ShaderBank::GetVertexShader(const std::string& _path)
{
	if (vershader.count(_path))
	{
		return vershader[_path].Get();
	}
	return nullptr;
}

ID3D11InputLayout* ShaderBank::GetInputLayout(const std::string& _path)
{
	if (inputlayout.count(_path))
	{
		return inputlayout[_path].Get();
	}
	return nullptr;
}
