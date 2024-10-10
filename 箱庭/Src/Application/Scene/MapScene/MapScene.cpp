﻿#include"MapScene.h"

#include"../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Enemy/Cal/Cal.h"
#include"../../AssetRepository/AssetRepository.h"
#include"json.hpp"

void MapScene::Init()
{
	//nlohmann::json j;
	//std::ifstream inFile("Asset/Data/GameObject/map.json");
	//inFile >> j;

	std::shared_ptr<Terrain> _terrain;
	std::shared_ptr<KdModelData>_model;
	//
	////for文でjsonファイルの中身を入れている
	//for (auto& item : j)
	//{
	//	_terrain = std::make_shared<Terrain>();
	//	_model = std::make_shared<KdModelData>();

	//	Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };

	//	_model = AssetRepository::Instance().GetModel(item["name"]);

	//	Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["posX"],item["posY"] ,item["posZ"] });
	//	Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scaleX"],item["scaleY"] ,item["scaleZ"] });
	//	Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);

	//	Math::Matrix mat = scaleMat * rotMat * transMat;

	//	_terrain->SetMatrix(mat);
	//	_terrain->SetModel(_model);

	//	AddObject(_terrain);

	//}
	Math::Matrix mat = Math::Matrix::CreateTranslation({ 100.f,-1.5f,0.f });
	_model = AssetRepository::Instance().GetModel("Cage");
	std::shared_ptr<Cal> _cal = std::make_shared<Cal>();
	_cal->SetMatrix(mat);
	_cal->SetModel(_model);
	AddObject(_cal);

	//平行光(ディレクショナルライト)								↓方向			↓RGB
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ -0.2,-1,-0.5f }, { 0.8f,0.8f,0.8f });

	//環境光(アンビエントライト)											↓色RGBA　デフォルト0.3
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.3f, 0.3f, 0.4f, 1 });

	KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.25f);

}
