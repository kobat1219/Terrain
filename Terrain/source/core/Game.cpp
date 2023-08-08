#include "Game.h"
#include "../directx/DX11Util.h"
#include "../core/Application.h"
#include "../imgui_dx11/imgui.h"
#include "../imgui_dx11/ImGuiManager.h"
#include "../imgui_dx11/ImGuiTemplate.h"
#include "../directx/DX11Settransform.h"
#include "Input.h"

#include <time.h>

using namespace DirectX;

void Game::Init()
{
	// ランダム初期化
	srand(time(NULL));
	// Windowのハンドル、クライアントの横幅、縦幅、フルスクリーンのフラグ
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT, false);

	ImGuiManager::Init();

	m_terrain.Init();

	// 平行光源をセット
	DX11LightInit(DirectX::XMFLOAT4(0.41f, 1.160f, 0.09f, 0));

	TurnOnAlphablend();
}

void Game::Update()
{
	ImGuiManager::NewFrame();

	// ************************************************************
	// ここから更新
	// ************************************************************

	//static int id = 0;
	//const char* items[] = { "nomal","nomal_set","star","hart","uzu" };
	ImGui::Begin(u8"地形調整");

	m_seed = m_terrain.GetSeed();
	ImGui::Text(u8"シード値");
	ImGui::SameLine();
	if (ImGui::Button(u8"ランダムシード"))
	{
		m_terrain.SetSeed(rand());
	}
	if (ImGui::InputInt("seed", &m_seed)) 
	{
		m_terrain.SetSeed(m_seed);
	}

	m_uvscale = m_terrain.GetUVScale();
	ImGui::Text(u8"UVスケール値");
	if (ImGui::DragFloat("scale", &m_uvscale)) 
	{
		m_terrain.SetUVScale(m_uvscale);
	}

	if (ImGui::Button(u8"地形生成"))
	{
		m_terrain.UpdateEditConstantData();
		m_terrain.CalNewMapCS();
	}

	ImGui::Text(u8"テクスチャ合成高さ");
	if (ImGui::DragFloat2("range", m_texrange, 0.1f))
	{
		m_terrain.SetTexHeight({ m_texrange[0], m_texrange[1]});
	}

	ImGui::End();

	ImGui::Begin(u8"テッセレーション調整距離");

	float len = m_terrain.GetMaxLength();
	ImGui::SliderFloat("len", &len, 1, 256);
	m_terrain.SetMaxLength(len);

	m_texrange[0]=m_terrain.GetTexHeight().x;
	m_texrange[1]=m_terrain.GetTexHeight().y;


	ImGui::End();

	ImGuiTemplate::ViewChangeViewer();
	ImGuiTemplate::CameraViewer(m_eye, m_lookat);
	ImGuiTemplate::FPSViewer();
	ImGuiTemplate::MemoryViewer();

	// ************************************************************
	// ここまで更新以下描画
	// ************************************************************
	float clearcolor[] = { 0, 0.5f, 0.5f, 1 };
	// 背景の描画（ターゲットバッファのクリア=>Zバッファクリア）
	DX11BeforeRender(clearcolor);

	XMFLOAT4X4 f4x4;

	// プロジェクション変換行列取得
	ALIGN16 XMMATRIX mat;

	mat = XMMatrixPerspectiveFovLH(
		PI / 4.0f,
		1600.0f / 900.0f,
		0.1f,
		1000
	);

	XMStoreFloat4x4(&f4x4, mat);

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, f4x4);

	// ビュー変換行列取得
	ALIGN16 XMVECTOR Eye = XMVectorSet(
		m_eye.x,
		m_eye.y,
		m_eye.z,
		0.0f
	);
	ALIGN16 XMVECTOR At = XMVectorSet(
		m_lookat.x,
		m_lookat.y,
		m_lookat.z,
		0.0f
	);
	ALIGN16 XMVECTOR Up = XMVectorSet(
		0,
		1,
		0,
		0.0f
	);

	mat = XMMatrixLookAtLH(Eye, At, Up);

	XMStoreFloat4x4(&f4x4, mat);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, f4x4);

	mat = XMMatrixTranslation(0, 0, 0);

	XMStoreFloat4x4(&f4x4, mat);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, f4x4);

	m_terrain.Draw(m_eye);

	ImGuiManager::Draw();

	// 描画 （スワップ）
	DX11AfterRender();
}

void Game::Finalize()
{	
	ImGuiManager::UnInit();
	
	DX11LightUninit();

	DX11Uninit();
}
