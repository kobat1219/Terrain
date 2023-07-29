//--------------------------------------------------------------
// Linker
//--------------------------------------------------------------
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment (lib,"directxtex.lib")	//�p�X�̐ݒ肪�K�v	�O���V���{���̃G���[�͎��̂��Ȃ�
#pragma comment (lib,"d3dcompiler.lib")

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "Application.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	�G���g���|�C���g
//!	@param	�C���X�^���X�n���h��
//!	@param	
//!	@param	�N�����̈���������
//!	@param	�E�C���h�E�\�����[�h
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//!	@note	
//==============================================================================
INT APIENTRY WinMain(HINSTANCE  h_hInst,
					 HINSTANCE  h_hPrevInst,
					 LPSTR		h_lpszArgs,
					 int		h_nWinMode)
{
	// �A�v���P�[�V������������
	Application* App = Application::Instance();		// �C���X�^���X�擾
	App->Init( h_hInst );

	// �E�C���h�E��\������
	ShowWindow( App->GetHWnd(), h_nWinMode );
	UpdateWindow( App->GetHWnd() );

	// ���C�����[�v
	long ret = App->MainLoop();

	// �A�v���P�[�V�����I������
	App->Dispose();						

	return ret;
}

/*EOF*/