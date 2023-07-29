#pragma once
#include	<d3d11.h>
#include	<wrl/client.h>

// ComPtr�̓X�}�|�̂��ƁB
using Microsoft::WRL::ComPtr;

/// <summary>
/// DX�O���t�B�b�N�N���X
/// </summary>
class DirectXGraphics {
private:
	DirectXGraphics() {}	//�����
	ComPtr<ID3D11Device>			m_lpDevice;					// DIRECT3DDEVICE11�f�o�C�X
	ComPtr<ID3D11DeviceContext>		m_lpImmediateContext;		// DIRECT3DDEVICE11�f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>			m_lpSwapChain;				// �X���b�v�`�F�C��

	ComPtr<ID3D11RenderTargetView>	m_lpRenderTargetView;		// �����_�[�^�[�Q�b�g�r���[
	ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;		// �y�o�b�t�@�A�X�e���V���o�b�t�@
	ComPtr<ID3D11DepthStencilState>	m_depthStencilState;		// �y�o�b�t�@�A�X�e���V���X�e�[�g
	ComPtr<ID3D11DepthStencilView>	m_depthStencilView;			// �y�o�b�t�@�A�X�e���V���r���[
	ComPtr<ID3D11RasterizerState>	m_rasterSolidState;				// ���X�^�[�X�e�[�^�X
	ComPtr<ID3D11RasterizerState>	m_rasterWireState;				// ���X�^�[�X�e�[�^�X

	D3D_DRIVER_TYPE					m_DriverType;				// �h���C�o�^�C�v
	D3D_FEATURE_LEVEL				m_FeatureLevel;				// �@�\���x��

	ComPtr<ID3D11BlendState>		m_alphaEnableBlendingState;		// �A���t�@�u�����h�X�e�[�g�i�L���j
	ComPtr<ID3D11BlendState>		m_alphaDisableBlendingState;	// �A���t�@�u�����h�X�e�[�g�i�����j

	ComPtr<ID3D11SamplerState>		m_samplerstate;					// �T���v���[�X�e�[�g

	int								m_Width = 0;				// �o�b�N�o�b�t�@�w�T�C�Y
	int								m_Height = 0;				// �o�b�N�o�b�t�@�x�T�C�Y
public:
	
	// �R�s�[�R���X�g���N�^���I�[�o�[���C�h�B�R�s�[������Ȃ��悤�ɁB
	DirectXGraphics(const DirectXGraphics&) = delete;
	DirectXGraphics& operator=(const DirectXGraphics&) = delete;
	DirectXGraphics(DirectXGraphics&&) = delete;
	DirectXGraphics& operator=(DirectXGraphics&&) = delete;

	// �f�X�g���N�^
	~DirectXGraphics() {
		// �������
		Exit();
	}

	// �C���X�^���X�擾
	static DirectXGraphics* GetInstance() {
		static DirectXGraphics instance;
		return &instance;
	}

	/// <summary>
	/// DirectX Grpaphics �̏���������
	/// </summary>
	/// <param name="hWnd">�E�C���h�E�n���h���l</param>
	/// <param name="Width">�E�C���h�E�T�C�Y�i���j</param>
	/// <param name="Height">�E�C���h�E�T�C�Y�i�����j</param>
	/// <param name="fullscreen">�t���X�N���[���ifalse window  true fullscreen )</param>
	/// <returns>
	/// false : ���s�@
	/// true  : ����
	/// </returns>
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool fullscreen);

	/// <summary>
	/// DirectX Grpaphics �̏I������
	/// </summary>
	void Exit();

	// �f�o�C�XGET
	ID3D11Device*	GetDXDevice() const {
		return m_lpDevice.Get();
	}

	// �C�~�f�B�G�C�g�f�o�C�XGET�B�C�~�f�B�G�C�g�͑����Ƃ����Ӗ��B
	// �Ȃ̂ł��̃C�~�f�B�G�C�g�ɓ`����Ƒ�����GPU�ɔ��s�����B
	// ����́A�f�o�C�X�R���e�L�X�g�Ɠ����B
	// ���C���X���b�h�݂̂Ŏg����B�}���`�X���b�h�̏ꍇ�́A���C���ɓ`���Ȃ��Ƃ����Ȃ��B
	ID3D11DeviceContext* GetImmediateContext() const {
		return m_lpImmediateContext.Get();
	}

	// SWAP�`�F�C��GET
	IDXGISwapChain* GetSwapChain()const {
		return m_lpSwapChain.Get();
	}

	// �����_�����O�^�[�Q�b�gGET
	ID3D11RenderTargetView* GetRenderTargetView() const {
		return m_lpRenderTargetView.Get();
	}

	// depthstencil view
	ID3D11DepthStencilView* GetDepthStencilView() const {
		return m_depthStencilView.Get();
	}

	// �r���[�|�[�g�̍������擾����
	int GetViewPortHeight() const {
		return m_Height;
	}

	// �r���[�|�[�g�̕����擾����
	int GetViewPortWidth() const {
		return m_Width;
	}

	// �A���t�@�u�����h�L����
	void TurnOnAlphaBlending();

	// �A���t�@�u�����h������
	void TurnOffAlphaBlending();

	// Z�o�b�t�@������
	void TurnOffZbuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// �^�[�Q�b�g
			rtvtable,								// �r���[�e�[�u��
			nullptr									// �[�x�o�b�t�@�Ȃ�
		);
	}

	// Z�o�b�t�@�L����
	void TurnOnZBuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// �^�[�Q�b�g
			rtvtable,								// �r���[�e�[�u��
			m_depthStencilView.Get()				// �[�x�o�b�t�@�Ȃ�
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
