#include "GimmickScene.h"

#include"../../GameObject/Gimmick/Relief/Relief.h"
#include"../../GameObject/Gimmick/Nidle/Nidle.h"
#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

#include"json.hpp"


void GimmickScene::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/Gimmick.json");
	inFile >> j;

	std::shared_ptr<Relief> _relief;
	std::shared_ptr<Nidle> _nidle;
	std::shared_ptr<KdModelData>_model;
	for (auto& item : j)
	{
		_model = std::make_shared<KdModelData>();

		Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };
		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["posX"],item["posY"] ,item["posZ"] });
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
	}
}

void GimmickScene::Event()
{
	if (m_count > RELIEFCOUNT)
	{

	}
}

