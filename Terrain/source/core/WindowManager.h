#pragma once

#include	<Windows.h>

class WindowCallback;

/**
* @brief	�E�C���h�E�֘A�N���X
*/
class WindowManager
{
	HWND				m_Handle;		// �n���h��
	MSG					m_Message;		// ���b�Z�[�W
	WindowCallback*		m_cpCallback;	// �R�[���o�b�N

public:

	static WindowManager* Instance();

	bool ExecMessage();

	bool RegisterClass( HINSTANCE	  hInstance,
						const char* h_ClassName,
						unsigned long h_Style );

	void SetWindow(HINSTANCE		h_Instance,
		unsigned long	h_Style,
		unsigned long	h_ExStyle,
		HWND			h_Parent,
		long			h_Width,
		long			h_Height,
		const char*		h_ClassName,
		const char* h_Title,
		bool			FULLSCREEN);

	long GetMessage() const;

	HWND GetHandle() const;

	WindowCallback* GetCallback() const;

private:
	WindowManager();
	virtual ~WindowManager();
	WindowManager( const WindowManager& );
	WindowManager& operator = (const WindowManager&) {}
};


/*EOF*/