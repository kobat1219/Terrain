#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <string>

class ImGuiManager
{
public:
	static void Init();

	static void NewFrame();

	static void Draw();

	static void UnInit();

	static void Test();

	static LRESULT WndProcHandler(HWND   h_Handle, UINT   h_Message, WPARAM h_WParam, LPARAM h_LParam);
};

