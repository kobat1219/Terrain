#pragma once

/**
 Include
*/
#include	<Windows.h>
#include	<stdio.h>
#include	<cinttypes>

/**
* @brief	アプリケーションクラス
*/
class Application
{
public:
	static const char*			WINDOW_TITLE;
	static const char*			WINDOW_CLASS_NAME;

	static const uint32_t		WINDOW_STYLE_WINDOWED;
	static const uint32_t		WINDOW_EX_STYLE_WINDOWED;		
	static const uint32_t		WINDOW_STYLE_FULL_SCREEN;		// = (WS_VISIBLE | WS_POPUP);使ってない
	static const uint32_t		WINDOW_EX_STYLE_FULL_SCREEN;	// = (0);使ってない

	static const uint32_t		CLIENT_WIDTH;
	static const uint32_t		CLIENT_HEIGHT;

	static uint32_t				SYSTEM_WIDTH;
	static uint32_t				SYSTEM_HEIGHT;

	static const float			FPS;

private:
	HWND					m_hWnd;							// Windowハンドル
	HINSTANCE				m_hInst;						// インスタンスハンドル
	uint32_t				m_SystemCounter;				// システムカウンタ。使ってない。
	FILE*					m_fp;							// デバッグ用コンソール

private:
	Application();											// コンストラクタ
	
	Application( const Application& );					// コピー
	Application& operator = (const Application&) {}		// =	

public:
	virtual ~Application();								// デストラクタ

	bool Init( HINSTANCE h_cpInstance );				// システム有効化
	void Dispose();										// システム無効化
	unsigned long MainLoop();								// メインループ

	// メンバ取得関数
	static Application* Instance();						// インスタンス取得
	HWND			 	GetHWnd() { return m_hWnd; }	// ウィンドウハンドル
	HINSTANCE			GetHInst() { return m_hInst; }	// インスタンスハンドル
};

/*EOF*/