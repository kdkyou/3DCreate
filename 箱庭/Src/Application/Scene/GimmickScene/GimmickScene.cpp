#include "GimmickScene.h"

#include"../../GameObject/Gimmick/Relief/Relief.h"
#include"../../GameObject/Gimmick/Nidle/Nidle.h"
#include"../../GameObject/Enemy/Megaro/Megaro.h"
#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

#include"json.hpp"


void GimmickScene::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/gimmick.json");
	inFile >> j;

	std::shared_ptr<Relief> _relief;
	std::shared_ptr<Nidle> _nidle;
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

			
		if (item["name"] == "Nidle")
		{
			_nidle = std::make_shared<Nidle>();
			std::shared_ptr<KdModelWork> _Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/Nidle/Nidle.gltf");
			_nidle->SetMatrix(_mat);
			_nidle->SetModel(_Model);
			AddObject(_nidle);
		}
		else if (item["name"] == "Relief")
		{
			_relief = std::make_shared<Relief>();
			_model = AssetRepository::Instance().GetModel(item["name"]);
			_relief->SetMatrix(_mat);
			_relief->SetModel(_model);
			AddObject(_relief);
		}
		else if (item["name"] == "Megaro")
		{
			/*_megaro = std::make_shared<Megaro>();
			_model = AssetRepository::Instance().GetModel(item["name"]);
			_megaro->SetMatrix(_mat);
			_megaro->SetModel(_model);
			_megaro->SetPos(pos);
			AddObject(_megaro);*/
		}
	}

	m_count = 0;
	time = 0;
}

void GimmickScene::Event()
{

	if (GetAsyncKeyState('P'))m_count = 3;
	if (m_count >= RELIEFCOUNT)
	{
		time++;
		if (time > 180)
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
			KdAudioManager::Instance().StopAllSound();
		}
	}
}

