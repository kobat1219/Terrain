//*****************************************************************************
//!	@file	Application.cpp
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	
//*****************************************************************************

///TODO:ゲーム部分のクラス化

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>

#include "Application.h"
#include "WindowManager.h"
#include "TimeManager.h"
#include "Input.h"
#include "../directx/DirectXGraphics.h"
#include "Game.h"

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------

const char*			Application::WINDOW_TITLE = "Terrain";

const char*			Application::WINDOW_CLASS_NAME = "win32app";

const uint32_t		Application::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t		Application::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t		Application::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t		Application::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t		Application::CLIENT_WIDTH = 1600;
const uint32_t		Application::CLIENT_HEIGHT = 900;

uint32_t			Application::SYSTEM_WIDTH = 0;
uint32_t			Application::SYSTEM_HEIGHT = 0;

const float			Application::FPS = 60;

//==============================================================================
//!	@fn		CApplication
//!	@brief	コンストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application :: Application(): m_SystemCounter		( 0 )
{}

//==============================================================================
//!	@fn		~Application
//!	@brief	デストラクタ
//!	@param	
//!	@retval	
//==============================================================================
Application :: ~Application()
{
	Dispose();
}

//==============================================================================
//!	@fn		GetInstance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
Application* Application::Instance()
{
	static Application Instance;

	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	インスタンスハンドル
//!	@retval	
//==============================================================================
bool Application :: Init( HINSTANCE h_Instance )
{
	// メモリーリークを検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	// コンソールを割り当てる
	AllocConsole();

	// 標準出力の割り当て
	freopen_s(&m_fp, "CON", "w", stdout);    

	// 幅と高さ初期化
	//InitSystemWindowHeight();

	// ウインドウ作成
	WindowManager* window = WindowManager::Instance();
	window->RegisterClass( h_Instance, WINDOW_CLASS_NAME, CS_OWNDC );

	window->SetWindow( h_Instance,
					   WINDOW_STYLE_WINDOWED,
					   WINDOW_EX_STYLE_WINDOWED,
					   NULL,
					   CLIENT_WIDTH + SYSTEM_WIDTH,
					   CLIENT_HEIGHT + SYSTEM_HEIGHT,
					   WINDOW_CLASS_NAME,
					   WINDOW_TITLE,
					   false);
			
	// HWND
	m_hWnd = window->GetHandle();

	//
	m_hInst = h_Instance;
	return true;
}

//==============================================================================
//!	@fn		Dispose
//!	@brief  終了処理
//!	@param	
//!	@retval	
//==============================================================================
void Application :: Dispose()
{
	// 標準出力クローズ
	fclose(m_fp);
	// コンソール開放
	::FreeConsole();

	return;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	メインループ
//!	@param	
//!	@retval	メッセージID
//==============================================================================
unsigned long Application :: MainLoop()
{
	MSG		msg;	
	ZeroMemory( &msg, sizeof( msg ) );	

	WindowManager* window = WindowManager::Instance();
	
	Time* _time = Time::GetInstance();
	_time->Init();

	// ゲームの初期処理
	Game::Instance().Init();

	while (window->ExecMessage()) {

		_time->Update();

		Input::Update();

		Game::Instance().Update();
	}

	// ゲームの終了処理
	Game::Instance().Finalize();

	return window->GetMessage();
}

/*EOF*/