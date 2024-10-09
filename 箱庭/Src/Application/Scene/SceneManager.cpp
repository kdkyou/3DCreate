#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include"MapScene/MapScene.h"
#include"GimmickScene/GimmickScene.h"
#include"DiceScene/DiceScene.h"

#include"../AssetRepository/AssetRepository.h"
#include"../GameObject/Terrain/Terrain.h"

#include"../GameObject/Gimmick/Nidle/Nidle.h"
#include"../GameObject/Gimmick/FallPillar/FallPillar.h"
#include"../GameObject/Gimmick/RotateBridge/RotateBridge.h"
#include"../GameObject/Gimmick/Wall/Wall.h"
#include"../GameObject/Gimmick/BreakWall/BreakWall.h"
#include"../GameObject/Gimmick/ArrowBox/ArrowBox.h"
#include"../GameObject/Gimmick/PitFall/PitFall.h"
#include"../GameObject/Gimmick/SlideDoor/SlideDoor.h"


void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();

	if (m_gimmickScene)
	{
		m_gimmickScene->Update();
	}
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
	if (m_gimmickScene)
	{
		m_gimmickScene->PostUpdate();
	}
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	if (m_mapScene)
	{
		m_mapScene->Draw();
	}
	if (m_gimmickScene)
	{
		m_gimmickScene->Draw();
	}
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	if (m_gimmickScene)
	{
		m_gimmickScene->DrawSprite();
	}
	m_currentScene->DrawSprite();

}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetMapObjList()
{
	// TODO: return ステートメントをここに挿入します
	return m_mapScene->GetObjList();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetGimmickObjList()
{
	// TODO: return ステートメントをここに挿入します
	return m_gimmickScene->GetObjList();
}

const int& SceneManager::GetReliefCount()
{
	// TODO: return ステートメントをここに挿入します
	return m_gimmickScene->GetCount();
}

void SceneManager::AddReliefCount()
{
	m_gimmickScene->IncreaseCount();
}


void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_currentScene->AddObject(obj);
}

void SceneManager::AddGimmick(const std::shared_ptr<KdGameObject>& obj)
{
	m_gimmickScene->AddObject(obj);
}

void SceneManager::Imgui()
{
	ImGui::Begin("Create");

	CreateObject();
	//CreateGimmick();

	ImGui::End();

	ImGui::Begin("Controll");
	ImGui::End();
}

void SceneManager::AddMapObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_mapScene->AddObject(obj);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		m_gimmickScene = nullptr;
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		if (!m_gimmickScene)m_gimmickScene = std::make_shared<GimmickScene>();
		break;
	}

	if (!m_mapScene)m_mapScene = std::make_shared<MapScene>();

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}

void SceneManager::CreateObject()
{

	if (ImGui::Button("Normal"))
	{
		CreateMapObject(ObjectName::CathedralNormal);
	}
	if (ImGui::Button("Arch"))
	{
		CreateMapObject(SceneManager::ObjectName::CathedralArch);
	}
	if (ImGui::Button("Rod"))
	{
		CreateMapObject(SceneManager::ObjectName::CathedralRod);
	}
	if (ImGui::Button("Sentral"))
	{
		CreateMapObject(SceneManager::ObjectName::CathedralSentral);
	}
	if (ImGui::Button("Wall"))
	{
		CreateMapObject(SceneManager::ObjectName::CathedralWall);
	}
	if (ImGui::Button("Bridge"))
	{
		CreateMapObject(SceneManager::ObjectName::Bridge);
	}
	ImGui::Text("Fence");
	if (ImGui::Button("FNormal"))
	{
		CreateMapObject(SceneManager::ObjectName::FenceNormal);
	}
	if (ImGui::Button("OneBreak"))
	{
		CreateMapObject(SceneManager::ObjectName::FenceOneBreak);
	}
	if (ImGui::Button("Breaked"))
	{
		CreateMapObject(SceneManager::ObjectName::FenceBreaked);
	}
	if (ImGui::Button("Pillar"))
	{
		CreateMapObject(SceneManager::ObjectName::Pillar);
	}
	if (ImGui::Button("Relief"))
	{
		CreateMapObject(SceneManager::ObjectName::Relief);
	}
	if (ImGui::Button("Stairs"))
	{
		CreateMapObject(SceneManager::ObjectName::Stairs);
	}
	if (ImGui::Button("Tail"))
	{
		CreateMapObject(SceneManager::ObjectName::Tail);
	}
	if (ImGui::Button("Temple"))
	{
		CreateMapObject(SceneManager::ObjectName::Temple);
	}
	ImGui::Text("Box");
	if (ImGui::Button("Box"))
	{
		CreateMapObject(SceneManager::ObjectName::Box);
	}
	if (ImGui::Button("SepBox"))
	{
		CreateMapObject(SceneManager::ObjectName::SepBox);
	}
	if (ImGui::Button("CorBox"))
	{
		CreateMapObject(SceneManager::ObjectName::CorBox);
	}
	if (ImGui::Button("WallBox"))
	{
		CreateMapObject(SceneManager::ObjectName::WallBox);
	}
	if (ImGui::Button("BreakWall"))
	{
		CreateMapObject(SceneManager::ObjectName::BreakWall);
	}
	if (ImGui::Button("Cal"))
	{
		CreateMapObject(SceneManager::ObjectName::Cal);
	}
}

void SceneManager::CreateMapObject(ObjectName name)
{
	std::shared_ptr<Terrain> test;
	test = std::make_shared<Terrain>();
	test->Init();
	std::shared_ptr<KdModelData> model;
	model = std::make_shared<KdModelData>();

	std::shared_ptr<MapObject> _map;
	_map = std::make_shared<MapObject>();

	switch (name)
	{
	case SceneManager::ObjectName::CathedralArch:
		model = AssetRepository::Instance().GetModel("CatheArch");
		_map->m_name = "CatheArch";
		break;
	case SceneManager::ObjectName::CathedralNormal:
		model = AssetRepository::Instance().GetModel("CatheNormal");
		_map->m_name = "CatheNormal";
		break;
	case SceneManager::ObjectName::CathedralRod:
		model = AssetRepository::Instance().GetModel("CatheRod");
		_map->m_name = "CatheRod";
		break;
	case SceneManager::ObjectName::CathedralSentral:
		model = AssetRepository::Instance().GetModel("CatheSentral");
		_map->m_name = "CatheSentral";
		break;
	case SceneManager::ObjectName::CathedralWall:
		model = AssetRepository::Instance().GetModel("CatheWall");
		_map->m_name = "CatheWall";
		break;
	case SceneManager::ObjectName::Bridge:
		model = AssetRepository::Instance().GetModel("Bridge");
		_map->m_name = "Bridge";
		break;
	case SceneManager::ObjectName::FenceNormal:
		model = AssetRepository::Instance().GetModel("FenceNormal");
		_map->m_name = "FenceNormal";
		break;
	case SceneManager::ObjectName::FenceOneBreak:
		model = AssetRepository::Instance().GetModel("FenceOneBreak");
		_map->m_name = "FenceOneBreak";
		break;
	case SceneManager::ObjectName::FenceBreaked:
		model = AssetRepository::Instance().GetModel("FenceBreaked");
		_map->m_name = "FenceBreaked";
		break;
	case SceneManager::ObjectName::Pillar:
		model = AssetRepository::Instance().GetModel("Pillar");
		_map->m_name = "Pillar";
		break;
	case SceneManager::ObjectName::Relief:
		model = AssetRepository::Instance().GetModel("Relief");
		_map->m_name = "Relief";
		break;
	case SceneManager::ObjectName::Stairs:
		model = AssetRepository::Instance().GetModel("Stairs");
		_map->m_name = "Stairs";
		break;
	case SceneManager::ObjectName::Tail:
		model = AssetRepository::Instance().GetModel("Tail");
		_map->m_name = "Tail";
		break;
	case SceneManager::ObjectName::Temple:
		model = AssetRepository::Instance().GetModel("Temple");
		_map->m_name = "Temple";
		break;
	case SceneManager::ObjectName::Box:
		model = AssetRepository::Instance().GetModel("Box");
		_map->m_name = "Box";
		break;
	case SceneManager::ObjectName::SepBox:
		model = AssetRepository::Instance().GetModel("SepBox");
		_map->m_name = "SepBox";
		break;
	case SceneManager::ObjectName::CorBox:
		model = AssetRepository::Instance().GetModel("CorBox");
		_map->m_name = "CorBox";
		break;
	case SceneManager::ObjectName::WallBox:
		model = AssetRepository::Instance().GetModel("WallBox");
		_map->m_name = "WallBox";
		break;
	case SceneManager::ObjectName::BreakWall:
		model = AssetRepository::Instance().GetModel("BreakWall");
		_map->m_name = "BreakWall";
		break;
	case SceneManager::ObjectName::Cal:
		model = AssetRepository::Instance().GetModel("Cal");
		_map->m_name = "Cal";
		break;
	default:
		break;
	}
	test->SetModel(model);
	AddMapObject(test);
	_map->m_obj = test;
	m_mapList.push_back(_map);
	m_spNow = test;

	m_scale = { 1,1,1 };
}

void SceneManager::CreateGimmick()
{
	ImGui::Text("Gimmick");
	if (ImGui::Button("Nidle"))
	{
		std::shared_ptr<Nidle> _nidle = std::make_shared<Nidle>();
		std::shared_ptr<KdModelWork> _Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/Nidle/Nidle.gltf");
		_nidle->SetModel(_Model);
		AddObject(_nidle);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Nidle";
		_map->m_obj = _nidle;
		m_gimmickList.push_back(_map);
		m_spNow = _nidle;

	}
	if (ImGui::Button("FallPillar"))
	{
		std::shared_ptr<KdModelWork> _Model;
		std::shared_ptr<FallPillar> _fall = std::make_shared<FallPillar>();
		_Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/FallPillar/Pillar.gltf");
		_fall->Init();
		_fall->SetModel(_Model);
		AddObject(_fall);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Fall";
		_map->m_obj = _fall;
		m_gimmickList.push_back(_map);
		m_spNow = _fall;
	}
	if (ImGui::Button("Rotate"))
	{
		std::shared_ptr<KdModelWork> _Model;
		std::shared_ptr<RotateBridge> _bridge = std::make_shared<RotateBridge>();
		_Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/RotateBridge/RotateBridge.gltf");
		std::shared_ptr<KdModelData> _model;
		_model = std::make_shared<KdModelData>();
		_model->Load("Asset/Models/Terrains/Gimmick/RotateBridge/BridgeUp.gltf");
		_bridge->SetModel(_Model);
		_bridge->SetModel(_model);
		AddObject(_bridge);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Rotate";
		_map->m_obj = _bridge;
		m_gimmickList.push_back(_map);
		m_spNow = _bridge;
	}
	if (ImGui::Button("BreakWall"))
	{
		std::shared_ptr<BreakWall> _break = std::make_shared<BreakWall>();
		std::shared_ptr<KdModelWork> _Model;
		_Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/BreakWall/BreakWall.gltf");
		_break->Init();
		_break->SetModel(_Model);
		AddObject(_break);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "BreakWall";
		_map->m_obj = _break;
		m_gimmickList.push_back(_map);
		m_spNow = _break;
	}
	if (ImGui::Button("Wall"))
	{
		std::shared_ptr<KdModelWork> _Model;
		std::shared_ptr<Wall> _wall = std::make_shared<Wall>();
		_Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/Wall/Wall.gltf");
		_wall->Init();
		_wall->SetModel(_Model);
		AddObject(_wall);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Wall";
		_map->m_obj = _wall;
		m_gimmickList.push_back(_map);
		m_spNow = _wall;
	}
	if (ImGui::Button("Arrow"))
	{
		std::shared_ptr<ArrowBox> _arrow = std::make_shared<ArrowBox>();
		std::shared_ptr<KdModelData> _model;
		_model = std::make_shared<KdModelData>();
		_model->Load("Asset/Models/Terrains/Gimmick/ArrowBox/ArrowBox.gltf");
		_arrow->Init();
		_arrow->SetModel(_model);
		AddObject(_arrow);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Arrow";
		_map->m_obj = _arrow;
		m_gimmickList.push_back(_map);
		m_spNow = _arrow;
	}

	if (ImGui::Button("Pit"))
	{
		std::shared_ptr<KdModelWork> _Model;
		std::shared_ptr<PitFall> _pit = std::make_shared<PitFall>();
		_Model = std::make_shared<KdModelWork>();
		_Model->SetModelData("Asset/Models/Terrains/Gimmick/PitFall/PitFall.gltf");
		_pit->Init();
		_pit->SetModel(_Model);
		AddObject(_pit);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Pit";
		_map->m_obj = _pit;
		m_gimmickList.push_back(_map);
		m_spNow = _pit;
	}
	if (ImGui::Button("Slide"))
	{
		std::shared_ptr<SlideDoor>_slide = std::make_shared<SlideDoor>();
		 std::shared_ptr<KdModelData> _model = std::make_shared<KdModelData>();
		_slide->Init();
		AddObject(_slide);
		std::shared_ptr<MapObject> _map;
		_map = std::make_shared<MapObject>();
		_map->m_name = "Slide";
		_map->m_obj = _slide;
		m_gimmickList.push_back(_map);
		m_spNow = _slide;
	}



}

void SceneManager::SaveMap()
{
}

void SceneManager::LoadMap()
{
}

void SceneManager::ClearMap()
{
}

void SceneManager::SaveGimic()
{
}

void SceneManager::LoadGimmick()
{
}
