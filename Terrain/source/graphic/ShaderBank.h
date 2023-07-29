#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<math.h>
#include	<vector>
#include	<wrl/client.h>
#include	<string>
#include	<unordered_map>

using Microsoft::WRL::ComPtr;

class ShaderBank
{
public:
	// �R�s�[�֎~�Y
	ShaderBank(const ShaderBank&) = delete;
	ShaderBank& operator=(const ShaderBank&) = delete;
	ShaderBank(ShaderBank&&) = delete;
	ShaderBank& operator=(ShaderBank&&) = delete;

	static ShaderBank& GetInstance() {
		static ShaderBank instance;
		return instance;
	}

	// 
	bool SetPixelShader(
		std::string _pixelshaderpath,
		ID3D11PixelShader** _pixelShaderAnser
	);
	
	bool SetVertexShader(
		std::string _vertecshaderpath,
		D3D11_INPUT_ELEMENT_DESC _layout[],
		unsigned int _numElements,
		ID3D11VertexShader** _vertexShaderAnser,
		ID3D11InputLayout** _inputLayerAnser
	);

	ID3D11PixelShader* GetPixelShader(const std::string& _path);

	ID3D11VertexShader* GetVertexShader(const std::string& _path);

	ID3D11InputLayout* GetInputLayout(const std::string& _path);

private:
	ShaderBank() {/*������B*/ }
private:
	// �s�N�Z���V�F�[�_�[
	std::unordered_map < std::string, ComPtr<ID3D11PixelShader>> pixelshader;

	// ���_�V�F�[�_�[
	std::unordered_map < std::string, ComPtr<ID3D11VertexShader>> vershader;
	
	// ���_���C�A�E�g
	std::unordered_map < std::string, ComPtr<ID3D11InputLayout>> inputlayout;
};

