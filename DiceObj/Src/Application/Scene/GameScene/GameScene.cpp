#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"


#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
#include"../../GameObject/Camera/FreeCamera/FreeCamera.h"


// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	
	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
//	std::shared_ptr<FreeCamera>		_camera = std::make_shared<FreeCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	//_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//ブルーム
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7);
	
	
	
}

void GameScene::Event()
{
}
