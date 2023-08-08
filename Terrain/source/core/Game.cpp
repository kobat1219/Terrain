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
	// �����_��������
	srand(time(NULL));
	// Window�̃n���h���A�N���C�A���g�̉����A�c���A�t���X�N���[���̃t���O
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT, false);

	ImGuiManager::Init();

	m_terrain.Init();

	// ���s�������Z�b�g
	DX11LightInit(DirectX::XMFLOAT4(0.41f, 1.160f, 0.09f, 0));

	TurnOnAlphablend();
}

void Game::Update()
{
	ImGuiManager::NewFrame();

	// ************************************************************
	// ��������X�V
	// ************************************************************

	//static int id = 0;
	//const char* items[] = { "nomal","nomal_set","star","hart","uzu" };
	ImGui::Begin(u8"�n�`����");

	m_seed = m_terrain.GetSeed();
	ImGui::Text(u8"�V�[�h�l");
	ImGui::SameLine();
	if (ImGui::Button(u8"�����_���V�[�h"))
	{
		m_terrain.SetSeed(rand());
	}
	if (ImGui::InputInt("seed", &m_seed)) 
	{
		m_terrain.SetSeed(m_seed);
	}

	m_uvscale = m_terrain.GetUVScale();
	ImGui::Text(u8"UV�X�P�[���l");
	if (ImGui::DragFloat("scale", &m_uvscale)) 
	{
		m_terrain.SetUVScale(m_uvscale);
	}

	if (ImGui::Button(u8"�n�`����"))
	{
		m_terrain.UpdateEditConstantData();
		m_terrain.CalNewMapCS();
	}

	ImGui::Text(u8"�e�N�X�`����������");
	if (ImGui::DragFloat2("range", m_texrange, 0.1f))
	{
		m_terrain.SetTexHeight({ m_texrange[0], m_texrange[1]});
	}

	ImGui::End();

	ImGui::Begin(u8"�e�b�Z���[�V������������");

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
	// �����܂ōX�V�ȉ��`��
	// ************************************************************
	float clearcolor[] = { 0, 0.5f, 0.5f, 1 };
	// �w�i�̕`��i�^�[�Q�b�g�o�b�t�@�̃N���A=>Z�o�b�t�@�N���A�j
	DX11BeforeRender(clearcolor);

	XMFLOAT4X4 f4x4;

	// �v���W�F�N�V�����ϊ��s��擾
	ALIGN16 XMMATRIX mat;

	mat = XMMatrixPerspectiveFovLH(
		PI / 4.0f,
		1600.0f / 900.0f,
		0.1f,
		1000
	);

	XMStoreFloat4x4(&f4x4, mat);

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, f4x4);

	// �r���[�ϊ��s��擾
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

	// �`�� �i�X���b�v�j
	DX11AfterRender();
}

void Game::Finalize()
{	
	ImGuiManager::UnInit();
	
	DX11LightUninit();

	DX11Uninit();
}
