#include"MapScene.h"

#include"../../GameObject/Terrain/Terrain.h"
#include"../../GameObject/Enemy/Cal/Cal.h"
#include"../../AssetRepository/AssetRepository.h"
#include"json.hpp"

void MapScene::Init()
{
	std::shared_ptr<Terrain> _terrain;
	std::shared_ptr<KdModelData>_model;
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/map.json");
	inFile >> j;

	std::shared_ptr<Terrain> test;
	std::shared_ptr<KdModelData> model;
//	std::shared_ptr<MapObject> _map;

	Math::Matrix mat = Math::Matrix::CreateTranslation({ 100.f,-1.5f,0.f });
	_model = AssetRepository::Instance().GetModel("Cage");
	std::shared_ptr<Cal> _cal = std::make_shared<Cal>();
	_cal->SetMatrix(mat);
	_cal->SetModel(_model);
	AddObject(_cal);

//	for (auto& item : j)
//	{
//		test = std::make_shared<Terrain>();
//		test->Init();
//		model = std::make_shared<KdModelData>();
////		_map = std::make_shared<MapObject>();
//
//		Math::Vector3 rot = { item["rot"]["X"],item["rot"]["Y"],item["rot"]["Z"] };
//
//		model = AssetRepository::Instance().GetModel(item["name"]);
//		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["pos"]["X"],item["pos"]["Y"] ,item["pos"]["Z"] });
//		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scale"]["X"],item["scale"]["Y"] ,item["scale"]["Z"] });
//		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);
//
////		_map->m_name = item["name"];
//
//		Math::Matrix mat = scaleMat * rotMat * transMat;
//		test->SetMatrix(mat);
//
//		test->SetModel(model);
//		test->SetRot(rot);
//		AddObject(test);
////		_map->m_obj = test;
////		m_mapList.push_back(_map);
//	}

	test = std::make_shared<Terrain>();
	test->Init();
	model = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/R'lyeh/OxtaTail/OxtaTail.gltf");
	test->SetModel(model);
	AddObject(test);

	/*mat = Math::Matrix::CreateTranslation({ 10.f,0.5f,0.f });
	_model = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/Grint/Grint.gltf");
	_cal = std::make_shared<Cal>();
	_cal->SetMatrix(mat);
	_cal->SetModel(_model);
	AddObject(_cal);*/




	

	//水面表現２　テクスチャを読み込む
	m_spnormalTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/GameObject/Shader/water.png");

	//水面表現6 PGUにテクスチャを転送
	KdShaderManager::Instance().m_StandardShader.SetWaterNormalTexture(*m_spnormalTex);

	

}
