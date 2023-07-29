#pragma once

#include	<Windows.h>

/**
* @brief	コールバッククラス
*/
class WindowCallback
{
public:
	WindowCallback(){};
	virtual ~WindowCallback(){};

	virtual LRESULT OnKeyDown	( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnKeyUp		( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnSysKeyDown( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnSysKeyUp	( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnClose		( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnDestroy	( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
	virtual LRESULT OnPaint		( HWND h_Handle, UINT h_Message, WPARAM h_WParam, LPARAM h_LParam );
 
};

/*EOF*/