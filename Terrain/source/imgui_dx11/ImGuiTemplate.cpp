#include "ImGuiTemplate.h"

#include "imgui.h"
#include <sstream>
#include <windows.h>
#include <psapi.h>

#include "../core/TimeManager.h"
#include "../directx/DX11Util.h"

using namespace MyEngine;

void ImGuiTemplate::CameraViewer(float3& _eye, float3& _lookat)
{
	ImGui::Begin("Camera");

	float eye[3] = { _eye.x,_eye.y ,_eye.z };
	float lookat[3] = { _lookat.x,_lookat.y ,_lookat.z };

	ImGui::DragFloat3("Eye", eye);
	ImGui::DragFloat3("LookAt", lookat);

	_eye.x = eye[0];
	_eye.y = eye[1];
	_eye.z = eye[2];

	_lookat.x = lookat[0];
	_lookat.y = lookat[1];
	_lookat.z = lookat[2];

	ImGui::End();
}
void ImGuiTemplate::MemoryViewer()
{
	HANDLE hProc = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX pmc;
	BOOL isSuccess = GetProcessMemoryInfo(
		hProc,
		(PROCESS_MEMORY_COUNTERS*)&pmc,
		sizeof(pmc));
	CloseHandle(hProc);
	if (isSuccess == FALSE) return;

	ImGui::Begin(u8"メモリ使用量");

	SIZE_T maxm = pmc.PrivateUsage - pmc.WorkingSetSize + pmc.PeakWorkingSetSize;
	if (maxm >1000000)
	{
		ImGui::TextColored({1,1,0,1}, "MaxMemoryUsage:%lld MB", maxm / 1000000);
	}
	else if (maxm > 100)
	{
		ImGui::TextColored({ 1,1,0,1 }, "MaxMemoryUsage:%lld KB", maxm / 100);
	}
	else
	{
		ImGui::TextColored({ 1,1,0,1 }, "MaxMemoryUsage:%lld Byte", maxm);
	}

	if (pmc.PrivateUsage>1000000)
	{
		ImGui::Text("NowMemoryUsage:%lld MB", pmc.PrivateUsage/1000000);
	}
	else if (pmc.PrivateUsage > 100)
	{
		ImGui::Text("NowMemoryUsage:%lld KB", pmc.PrivateUsage / 100);
	}
	else
	{
		ImGui::Text("NowMemoryUsage:%lld Byte", pmc.PrivateUsage);
	}

	ImGui::End();
}

void ImGuiTemplate::FPSViewer()
{
	ImGui::Begin("FPS");
	ImGui::Text("%lf", 1 / Time::GetInstance()->DeltaTime());
	ImGui::End();
}

void ImGuiTemplate::ViewChangeViewer()
{
	ImGui::Begin(u8"表示方法");

	if (ImGui::Button(u8"ソリッド"))
	{
		TurnSolid();
	}

	ImGui::SameLine();

	if (ImGui::Button(u8"ワイヤー"))
	{
		TurnWire();
	}

	ImGui::End();
}
