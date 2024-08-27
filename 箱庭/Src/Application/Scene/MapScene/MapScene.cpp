#include"MapScene.h"

#include"../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Enemy/Cal/Cal.h"
#include"../../AssetRepository/AssetRepository.h"
#include"json.hpp"

void MapScene::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/map.json");
	inFile >> j;

	std::shared_ptr<Terrain> _terrain;
	std::shared_ptr<KdModelData>_model;
	for (auto& item : j)
	{
		_terrain = std::make_shared<Terrain>();
		_model = std::make_shared<KdModelData>();

		Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };
		
		_model = AssetRepository::Instance().GetModel(item["name"]);

		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["posX"],item["posY"] ,item["posZ"] });
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scaleX"],item["scaleY"] ,item["scaleZ"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);

		Math::Matrix mat = scaleMat * rotMat * transMat;

		if (item["name"] == "Cal")
		{
			std::shared_ptr<Cal> _cal = std::make_shared<Cal>();
			_cal->SetMatrix(mat);
			_cal->SetModel(_model);
			AddObject(_cal);
		}
		else
		{
			_terrain->SetMatrix(mat);
			_terrain->SetModel(_model);

			AddObject(_terrain);
		}
	}
	Math::Matrix mat = Math::Matrix::CreateTranslation({ 100.f,-1.5f,0.f });
	_model = AssetRepository::Instance().GetModel("Cage");
	std::shared_ptr<Cal> _cal = std::make_shared<Cal>();
	_cal->SetMatrix(mat);
	_cal->SetModel(_model);
	AddObject(_cal);
	
}
