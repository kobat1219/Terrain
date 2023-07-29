#pragma once

/**
 Include
*/
#include	<Windows.h>
#include	<stdio.h>
#include	<cinttypes>

/**
* @brief	�A�v���P�[�V�����N���X
*/
class Application
{
public:
	static const char*			WINDOW_TITLE;
	static const char*			WINDOW_CLASS_NAME;

	static const uint32_t		WINDOW_STYLE_WINDOWED;
	static const uint32_t		WINDOW_EX_STYLE_WINDOWED;		
	static const uint32_t		WINDOW_STYLE_FULL_SCREEN;		// = (WS_VISIBLE | WS_POPUP);�g���ĂȂ�
	static const uint32_t		WINDOW_EX_STYLE_FULL_SCREEN;	// = (0);�g���ĂȂ�

	static const uint32_t		CLIENT_WIDTH;
	static const uint32_t		CLIENT_HEIGHT;

	static uint32_t				SYSTEM_WIDTH;
	static uint32_t				SYSTEM_HEIGHT;

	static const float			FPS;

private:
	HWND					m_hWnd;							// Window�n���h��
	HINSTANCE				m_hInst;						// �C���X�^���X�n���h��
	uint32_t				m_SystemCounter;				// �V�X�e���J�E���^�B�g���ĂȂ��B
	FILE*					m_fp;							// �f�o�b�O�p�R���\�[��

private:
	Application();											// �R���X�g���N�^
	
	Application( const Application& );					// �R�s�[
	Application& operator = (const Application&) {}		// =	

public:
	virtual ~Application();								// �f�X�g���N�^

	bool Init( HINSTANCE h_cpInstance );				// �V�X�e���L����
	void Dispose();										// �V�X�e��������
	unsigned long MainLoop();								// ���C�����[�v

	// �����o�擾�֐�
	static Application* Instance();						// �C���X�^���X�擾
	HWND			 	GetHWnd() { return m_hWnd; }	// �E�B���h�E�n���h��
	HINSTANCE			GetHInst() { return m_hInst; }	// �C���X�^���X�n���h��
};

/*EOF*/