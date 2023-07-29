//--------------------------------------------------------------
// Linker
//--------------------------------------------------------------
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment (lib,"directxtex.lib")	//パスの設定が必要	外部シンボルのエラーは実体がない
#pragma comment (lib,"d3dcompiler.lib")

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "Application.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	インスタンスハンドル
//!	@param	
//!	@param	起動時の引数文字列
//!	@param	ウインドウ表示モード
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//!	@note	
//==============================================================================
INT APIENTRY WinMain(HINSTANCE  h_hInst,
					 HINSTANCE  h_hPrevInst,
					 LPSTR		h_lpszArgs,
					 int		h_nWinMode)
{
	// アプリケーション初期処理
	Application* App = Application::Instance();		// インスタンス取得
	App->Init( h_hInst );

	// ウインドウを表示する
	ShowWindow( App->GetHWnd(), h_nWinMode );
	UpdateWindow( App->GetHWnd() );

	// メインループ
	long ret = App->MainLoop();

	// アプリケーション終了処理
	App->Dispose();						

	return ret;
}

/*EOF*/