#include	<d3d11.h>
#include	<DirectXMath.h>
#include	"DirectxGraphics.h"
#include	"../graphic/Shader.h"
#include	"../core/Memory.h"
#include	"DX11Settransform.h"
#include "DX11Util.h"

DirectXGraphics* GetDX11Obj() {
	return DirectXGraphics::GetInstance();
}

ID3D11Device* GetDX11Device() {
	return DirectXGraphics::GetInstance()->GetDXDevice();
}

ID3D11DeviceContext*	GetDX11DeviceContext() {
	return DirectXGraphics::GetInstance()->GetImmediateContext();
}

bool DX11Init(HWND hwnd, int width, int height, bool fullscreen) {
	bool sts;

	sts = DirectXGraphics::GetInstance()->Init(hwnd, width, height, fullscreen);
	if (!sts) {
		MessageBox(hwnd, "DX11 init error", "error", MB_OK);
		return false;
	}

	sts = DX11SetTransform::GetInstance()->Init();
	if (!sts) {
		MessageBox(NULL, "SetTransform error", "Error", MB_OK);
		return false;
	}

	return true;
}

void DX11Uninit() {

	DX11SetTransform::GetInstance()->Uninit();

	// 解放処理
	DirectXGraphics::GetInstance()->Exit();

}

void DX11BeforeRender(float ClearColor[]) {
	// ターゲットバッファクリア
	DirectXGraphics::GetInstance()->GetImmediateContext()->ClearRenderTargetView(
		DirectXGraphics::GetInstance()->GetRenderTargetView(), ClearColor);
	// Zバッファクリア
	DirectXGraphics::GetInstance()->GetImmediateContext()->ClearDepthStencilView(
		DirectXGraphics::GetInstance()->GetDepthStencilView(), 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11AfterRender() {
	// ｓｗａｐ
	DirectXGraphics::GetInstance()->GetSwapChain()->Present(0, 0);
}

int DX11GetScreenWidth() {
	return DirectXGraphics::GetInstance()->GetViewPortWidth();
}

int DX11GetScreenHeight() {
	return DirectXGraphics::GetInstance()->GetViewPortHeight();
}

void TurnOffZbuffer() {
	DirectXGraphics::GetInstance()->TurnOffZbuffer();
}

void TurnOnZbuffer() {
	DirectXGraphics::GetInstance()->TurnOnZBuffer();
}

void TurnOnAlphablend() {
	DirectXGraphics::GetInstance()->TurnOnAlphaBlending();
}

void TurnOffAlphablend() {
	DirectXGraphics::GetInstance()->TurnOffAlphaBlending();
}

void TurnWire()
{
	DirectXGraphics::GetInstance()->TurnWire();
}

void TurnSolid()
{
	DirectXGraphics::GetInstance()->TurnSolid();
}
