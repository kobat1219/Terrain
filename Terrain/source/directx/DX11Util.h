#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	"DirectxGraphics.h"

DirectXGraphics* GetDX11Obj();
ID3D11Device* GetDX11Device();
ID3D11DeviceContext*	GetDX11DeviceContext();

/// <summary>
/// DX�̏�����
/// </summary>
/// <param name="hwnd" >Window�̃n���h��</param>
/// <param name="width">�N���C�A���g�̉���</param>
/// <param name="height">�N���C�A���g�̏c��</param>
/// <param name="fullscreen">�t���X�N���[���̃t���O</param>
/// <returns>�������̐����t���O</returns>
bool DX11Init(HWND hwnd, int width, int height, bool fullscreen);

/// <summary>
/// DX�̉��
/// </summary>
void DX11Uninit();

/// <summary>
/// �w�i�̕`��i�^�[�Q�b�g�o�b�t�@�̃N���A=>Z�o�b�t�@�N���A�j
/// </summary>
/// <param name="ClearColor">�w�i�̏������J���[</param>
void DX11BeforeRender(float ClearColor[]);

/// <summary>
/// �`�� �i�X���b�v�j
/// </summary>
void DX11AfterRender();

/// <summary>
/// �X�N���[���̉���
/// </summary>
/// <returns>�o�b�N�o�b�t�@�̉���</returns>
int DX11GetScreenWidth();

/// <summary>
/// �X�N���[���̏c��
/// </summary>
/// <returns>�o�b�N�o�b�t�@�̏c��</returns>
int DX11GetScreenHeight();

void TurnOffZbuffer();
void TurnOnZbuffer();

void TurnOnAlphablend();

void TurnOffAlphablend();

void TurnWire();

void TurnSolid();

