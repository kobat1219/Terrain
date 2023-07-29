//*****************************************************************************
//!	@file	WindowCallback.cpp
//!	@brief	
//!	@note	ウインドウコールバッククラス
//!	@author	T.Suzuki
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "WindowCallback.h"
//==============================================================================
//!	@fn		OnKeyUp
//!	@brief	キー押下
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnKeyUp( HWND   h_wnd,
								    UINT   h_Message,
									WPARAM h_WParam,
									LPARAM h_LParam )
{
	return DefWindowProc(h_wnd, h_Message, h_WParam, h_LParam );
}


//==============================================================================
//!	@fn		OnKeyDown
//!	@brief	キー押下
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnKeyDown( HWND   h_wnd, 
									  UINT   h_Message,
									  WPARAM h_WParam,
									  LPARAM h_LParam )
{
	switch (h_WParam) {
	case VK_ESCAPE:
		DestroyWindow(h_wnd);
	default:
		return DefWindowProc(h_wnd, h_Message, h_WParam, h_LParam);
	}
	return 0;
}

//==============================================================================
//!	@fn		OnSysKeyUp
//!	@brief	システムキー解放
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnSysKeyUp( HWND   h_wnd,
									   UINT   h_Message,
									   WPARAM h_WParam,
									   LPARAM h_LParam )
{	
	return DefWindowProc(h_wnd, h_Message, h_WParam, h_LParam );
}


//==============================================================================
//!	@fn		OnSysKeyDown
//!	@brief	システムキー押下
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnSysKeyDown( HWND   h_wnd,
									     UINT   h_Message,
									     WPARAM h_WParam,
									     LPARAM h_LParam )
{
	return DefWindowProc(h_wnd, h_Message, h_WParam, h_LParam );
}

//==============================================================================
//!	@fn		OnClose
//!	@brief	Ｘ
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnClose( HWND   h_wnd,
									UINT   h_Message,
									WPARAM h_WParam,
									LPARAM h_LParam )
{
	PostQuitMessage( 0 );
    return 0;
}

//==============================================================================
//!	@fn		OnDestroy
//!	@brief	終了
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnDestroy( HWND   h_wnd,
									  UINT   h_Message,
									  WPARAM h_WParam,
									  LPARAM h_LParam )
{
	PostQuitMessage( 0 );
	return 0;
}


//==============================================================================
//!	@fn		OnPaint
//!	@brief	再描画
//!	@param	
//!	@retval	
//==============================================================================
LRESULT WindowCallback :: OnPaint( HWND   h_wnd,
									UINT   h_Message,
									WPARAM h_WParam,
									LPARAM h_LParam )
{  
	return DefWindowProc(h_wnd, h_Message, h_WParam, h_LParam );
}

//******************************************************************************
//	End of file.
//******************************************************************************
