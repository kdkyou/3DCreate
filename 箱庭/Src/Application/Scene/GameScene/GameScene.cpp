#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Character/Player/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
#include"../../GameObject/Camera/FreeCamera/FreeCamera.h"

#include"../../GameObject/Enemy/Megaro/Megaro.h"
#include"../../GameObject/Weapon/Axe/Axe.h"

#include"../../AssetRepository/AssetRepository.h"

#include"../../GameObject/Dice/DiceManager.h"

#include"json.hpp"



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

	std::shared_ptr<Axe> _axe = std::make_shared<Axe>();
	_axe->Init();
	_axe->SetParent(_character);
	AddObject(_axe);

	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	//	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	//	std::shared_ptr<FreeCamera>		_camera = std::make_shared<FreeCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	//_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	DiceManager::GetInstance().SetCamera(_camera);

	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/enemy.json");
	inFile >> j;

	std::shared_ptr<Megaro> _megaro;
	std::shared_ptr<KdModelData>_model;
	for (auto& item : j)
	{
		_model = std::make_shared<KdModelData>();

		Math::Vector3 pos = { item["posX"],item["posY"] ,item["posZ"] };

		Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };
		Math::Matrix transMat = Math::Matrix::CreateTranslation(pos);
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scaleX"],item["scaleY"] ,item["scaleZ"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);

		Math::Matrix _mat = scaleMat * rotMat * transMat;

		_megaro = std::make_shared<Megaro>();
		_model = AssetRepository::Instance().GetModel(item["name"]);
		_megaro->SetMatrix(_mat);
		_megaro->SetModel(_model);
		_megaro->SetPos(pos);
		_megaro->SetTarget(_character);
		AddObject(_megaro);

	}




	KdAudioManager::Instance().Play("Asset/Sounds/BGM/R'lyeh.wav", true);
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/babul.wav", true);
}

void GameScene::Event()
{
	if (GetAsyncKeyState('I'))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
		KdAudioManager::Instance().StopAllSound();
	}
}
