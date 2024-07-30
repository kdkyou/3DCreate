#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include"../../GameObject/Dice/BlueDice/BlueDice.h"
#include"../../GameObject/Dice/RedDice/RedDice.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"


// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	m_spRDiceModel = std::make_shared<KdModelData>();
	m_spRDiceModel->Load("Asset/Models/Dice/RedDice/redDice.gltf");
	m_spBDiceModel = std::make_shared<KdModelData>();
	m_spBDiceModel->Load("Asset/Models/Dice/BlueDice/blueDice.gltf");


	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// ダイス初期化
	//===================================================================
	std::shared_ptr<BlueDice> _blueDice = std::make_shared<BlueDice>();
	_blueDice->SetModel(m_spBDiceModel);
	_blueDice->Init();
	AddObject(_blueDice);

	std::shared_ptr<RedDice> _redDice = std::make_shared<RedDice>();
	_redDice->SetModel(m_spRDiceModel);
	_redDice->Init();
	AddObject(_redDice);


	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	_blueDice->SetCamera(_camera);
	_redDice->SetCamera(_camera);

	_character->SetDice(_redDice, _blueDice);
}

void GameScene::Event()
{
}