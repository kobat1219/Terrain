#pragma once
#include "../graphic/Terrain.h"
#include <string>

/**------------------------------------------------------------
* @class ゲームクラス
-------------------------------------------------------------*/
class Game
{
	Game() {/*空実装*/ }

	Terrain m_terrain;
	
	int m_seed;
	float m_uvscale = 8;

	float m_texrange[2];

	std::string m_penname;

	MyEngine::float3 m_eye = { 0,50,35 };
	MyEngine::float3 m_lookat = { 0,0,0 };

public:
	// 複製禁止
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	// インスタンス取得
	static Game& Instance() {
		static Game instance;
		return instance;
	}
	// 初期化
	void Init();
	// 更新
	void Update();
	// 解放
	void Finalize();
};

/*******
* EOF
*******/