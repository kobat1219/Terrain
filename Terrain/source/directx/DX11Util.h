#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	"DirectxGraphics.h"

DirectXGraphics* GetDX11Obj();
ID3D11Device* GetDX11Device();
ID3D11DeviceContext*	GetDX11DeviceContext();

/// <summary>
/// DXの初期化
/// </summary>
/// <param name="hwnd" >Windowのハンドル</param>
/// <param name="width">クライアントの横幅</param>
/// <param name="height">クライアントの縦幅</param>
/// <param name="fullscreen">フルスクリーンのフラグ</param>
/// <returns>初期化の成功フラグ</returns>
bool DX11Init(HWND hwnd, int width, int height, bool fullscreen);

/// <summary>
/// DXの解放
/// </summary>
void DX11Uninit();

/// <summary>
/// 背景の描画（ターゲットバッファのクリア=>Zバッファクリア）
/// </summary>
/// <param name="ClearColor">背景の初期化カラー</param>
void DX11BeforeRender(float ClearColor[]);

/// <summary>
/// 描画 （スワップ）
/// </summary>
void DX11AfterRender();

/// <summary>
/// スクリーンの横幅
/// </summary>
/// <returns>バックバッファの横幅</returns>
int DX11GetScreenWidth();

/// <summary>
/// スクリーンの縦幅
/// </summary>
/// <returns>バックバッファの縦幅</returns>
int DX11GetScreenHeight();

void TurnOffZbuffer();
void TurnOnZbuffer();

void TurnOnAlphablend();

void TurnOffAlphablend();

void TurnWire();

void TurnSolid();

