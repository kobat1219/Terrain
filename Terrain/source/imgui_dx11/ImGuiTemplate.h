#pragma once
#include "../core/MyVariables.h"

/**----------------------------------------------
* @brief	ImGuiの表示テンプレート関数クラス
------------------------------------------------*/
class ImGuiTemplate
{
public:

	static void CameraViewer(MyEngine::float3& _eye, MyEngine::float3& _lookat);

	static void MemoryViewer();

	static void FPSViewer();

	static void ViewChangeViewer();
};

/*******
* EOF
*******/