#pragma once
#include "../graphic/Terrain.h"
#include <string>

/**------------------------------------------------------------
* @class �Q�[���N���X
-------------------------------------------------------------*/
class Game
{
	Game() {/*�����*/ }

	Terrain m_terrain;
	
	int m_seed;
	float m_uvscale = 8;

	float m_texrange[2];

	std::string m_penname;

	MyEngine::float3 m_eye = { 0,50,35 };
	MyEngine::float3 m_lookat = { 0,0,0 };

public:
	// �����֎~
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	// �C���X�^���X�擾
	static Game& Instance() {
		static Game instance;
		return instance;
	}
	// ������
	void Init();
	// �X�V
	void Update();
	// ���
	void Finalize();
};

/*******
* EOF
*******/