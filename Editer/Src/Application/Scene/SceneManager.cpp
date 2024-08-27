#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

#include"../main.h"

#include"magic_enum.hpp"

#include"../GameObject/Test.h"
#include"../AssetRepository/AssetRepository.h"

#include"json.hpp"
#include<fstream>
#include<iostream>

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
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
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

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_currentScene->AddObject(obj);
}

void SceneManager::Imgui()
{
	//＝＝＝＝＝＝＝＝始まり＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ImGui::Begin("Debug");


	if (ImGui::BeginMenu("File")) {
		if (ImGui::Button("Save")) {
			SaveMap();
		}
		if (ImGui::Button("Load")) {
			LoadMap();
		}
		if (ImGui::Button("SaveGimic")) {
			SaveGimic();
		}
		ImGui::EndMenu();
	}

	//オブジェクト追加
	ImGui::Text("objectCtreate");
	//if (ImGui::TreeNode("Cathedral"))
	{
		if (ImGui::Button("Normal"))
		{
			CreateObject(SceneManager::ObjectName::CathedralNormal);
		}
		if (ImGui::Button("Arch"))
		{
			CreateObject(SceneManager::ObjectName::CathedralArch);
		}
		if (ImGui::Button("Rod"))
		{
			CreateObject(SceneManager::ObjectName::CathedralRod);
		}
		if (ImGui::Button("Sentral"))
		{
			CreateObject(SceneManager::ObjectName::CathedralSentral);
		}
		if (ImGui::Button("Wall"))
		{
			CreateObject(SceneManager::ObjectName::CathedralWall);
		}
		if (ImGui::Button("Bridge"))
		{
			CreateObject(SceneManager::ObjectName::Bridge);
		}
		ImGui::Text("Fence");
		if (ImGui::Button("FNormal"))
		{
			CreateObject(SceneManager::ObjectName::FenceNormal);
		}
		if (ImGui::Button("OneBreak"))
		{
			CreateObject(SceneManager::ObjectName::FenceOneBreak);
		}
		if (ImGui::Button("Breaked"))
		{
			CreateObject(SceneManager::ObjectName::FenceBreaked);
		}
		if (ImGui::Button("Pillar"))
		{
			CreateObject(SceneManager::ObjectName::Pillar);
		}
		if (ImGui::Button("Relief"))
		{
			CreateObject(SceneManager::ObjectName::Relief);
		}
		if (ImGui::Button("Stairs"))
		{
			CreateObject(SceneManager::ObjectName::Stairs);
		}
		if (ImGui::Button("Tail"))
		{
			CreateObject(SceneManager::ObjectName::Tail);
		}
		if (ImGui::Button("Temple"))
		{
			CreateObject(SceneManager::ObjectName::Temple);
		}
		if (ImGui::Button("Megaro"))
		{
			CreateObject(SceneManager::ObjectName::Megaro);	
		}
		if (ImGui::Button("Cal"))
		{
			CreateObject(SceneManager::ObjectName::Cal);
		}

		ImGui::Text("Gimmick");
		if (ImGui::Button("Nidle"))
		{
			CreateGimmick();
		}
	}

	ImGui::Text("pos");
	if (ImGui::Button("PosReset"))
	{
		m_pos = {};
	}
	//ImGui::SliderFloat("pos.x", &m_pos.x, -100, 400);
	ImGui::InputFloat("pos.x", &m_pos.x, 0.1f);
	//ImGui::SliderFloat("pos.y", &m_pos.y, -100, 100);
	ImGui::InputFloat("pos.y", &m_pos.y, 0.1f);
	//ImGui::SliderFloat("pos.z", &m_pos.z, -100, 100);
	ImGui::InputFloat("pos.z", &m_pos.z, 0.1f);

	ImGui::Text("scale");
	if (ImGui::Button("ScaleReset"))
	{
		m_scale = { 1,1,1 };
	}
	ImGui::SliderFloat("scale.x", &m_scale.x, 0.1f, 10.0f);
	ImGui::SliderFloat("scale.y", &m_scale.y, 0.1f, 10.0f);
	ImGui::SliderFloat("scale.z", &m_scale.z, 0.1f, 10.0f);

	ImGui::Text("rotate");
	if (ImGui::Button("RotateReset"))
	{
		m_rot = {};
	}
	ImGui::SliderAngle("rotate.x", &m_rot.x,0);
	ImGui::SliderAngle("rotate.y", &m_rot.y, 0);
	ImGui::SliderAngle("rotate.z", &m_rot.z, 0);

	if (m_spNow != nullptr)
	{
		Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
		Math::Matrix _scale = Math::Matrix::CreateScale(m_scale);
		Math::Matrix _rotX = Math::Matrix::CreateRotationX(m_rot.x);
		Math::Matrix _rotY = Math::Matrix::CreateRotationY(m_rot.y);
		Math::Matrix _rotZ = Math::Matrix::CreateRotationZ(m_rot.z);
		Math::Matrix _mat = _scale * _rotX * _rotY * _rotZ * _trans;
		m_spNow->SetMatrix(_mat);
		m_spNow->SetRot(m_rot);
	}

	auto it = m_mapList.begin();
	int cont = m_mapList.size();
	
	//ImGui::ListBox("objList", num, (*it)->m_name, cont);

	

	ImGui::End();
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
	m_spNow = nullptr;
}

void SceneManager::CreateObject(SceneManager::ObjectName name)
{
	std::shared_ptr<Test> test;
	test = std::make_shared<Test>();
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
	case SceneManager::ObjectName::Megaro:
		model = AssetRepository::Instance().GetModel("Megaro");
		_map->m_name = "Megaro";
		break;
	case SceneManager::ObjectName::Cal:
		model = AssetRepository::Instance().GetModel("Cal");
		_map->m_name = "Cal";

	default:
		break;
	}
	test->SetModel(model);
	AddObject(test);
	m_spNow = test;
	_map->m_obj = test;
	m_mapList.push_back(_map);
	m_scale = { 1,1,1 };
	
}

void SceneManager::CreateGimmick()
{

	std::shared_ptr<Test> test;
	test = std::make_shared<Test>();
	test->Init();
	std::shared_ptr<KdModelData> model;
	model = std::make_shared<KdModelData>();

	model = AssetRepository::Instance().GetModel("Nidle");
	std::shared_ptr<MapObject> _gim;
	_gim = std::make_shared<MapObject>();
	_gim->m_name = "Nidle";
	test->SetModel(model);
	AddObject(test);
	m_spNow = test;
	_gim->m_obj = test;
	m_gimmickList.push_back(_gim);
	m_scale = { 1,1,1 };
}

void SceneManager::SaveMap()
{
	nlohmann::json j;
	std::ofstream outFile("map.json");
	if (outFile.is_open()) {
		auto it = m_mapList.begin();
		outFile << "[";
		while (it != m_mapList.end())
		{
			j["name"] = (*it)->m_name;
			j[ "posX"] = (*it)->m_obj->GetPos().x;
			j[ "posY"] = (*it)->m_obj->GetPos().y;
			j[ "posZ"] = (*it)->m_obj->GetPos().z;
			j["scaleX"] = (*it)->m_obj->GetScale().x;
			j["scaleY"] = (*it)->m_obj->GetScale().y;
			j["scaleZ"] = (*it)->m_obj->GetScale().z;
			j["rotX"] = (*it)->m_obj->GetRotate().x;
			j["rotY"] = (*it)->m_obj->GetRotate().y;
			j["rotZ"] = (*it)->m_obj->GetRotate().z;
		outFile << j.dump(4);
			it++;
			outFile << ",";
		}
		outFile << "]";
		outFile.close();
		Application::Instance().m_log.AddLog("Save\n");
	}
}

void SceneManager::LoadMap()
{
	/*auto it = m_mapList.begin();
	while(it!=m_mapList.end()) {
		(*it)->m_obj->Expired();
	}*/

	nlohmann::json j;
	std::ifstream inFile("map.json");
	inFile >> j;

	std::shared_ptr<Test> test;
	std::shared_ptr<KdModelData> model;
	std::shared_ptr<MapObject> _map;
	for (auto& item : j)
	{
		test = std::make_shared<Test>();
		test->Init();
		model = std::make_shared<KdModelData>();
		_map = std::make_shared<MapObject>();

		Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };

		model = AssetRepository::Instance().GetModel(item["name"]);
		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["posX"],item["posY"] ,item["posZ"] });
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scaleX"],item["scaleY"] ,item["scaleZ"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);

		_map->m_name = item["name"];

		Math::Matrix mat = scaleMat * rotMat * transMat;
		test->SetMatrix(mat);
		
		test->SetModel(model);
		test->SetRot(rot);
		AddObject(test);
		m_spNow = test;
		_map->m_obj = test;
		m_mapList.push_back(_map);
	}
	Application::Instance().m_log.AddLog("Load\n");
}

void SceneManager::ClearMap()
{
	auto it = m_mapList.begin();
	while (it != m_mapList.end()) {
		(*it)->m_obj->Expired();
	}
	m_mapList.clear();
}

void SceneManager::SaveGimic()
{
	nlohmann::json j;
	std::ofstream outFile("gimmick.json");
	if (outFile.is_open()) {
		auto it = m_gimmickList.begin();
		outFile << "[";
		while (it != m_gimmickList.end())
		{
			j["name"] = (*it)->m_name;
			j["posX"] = (*it)->m_obj->GetPos().x;
			j["posY"] = (*it)->m_obj->GetPos().y;
			j["posZ"] = (*it)->m_obj->GetPos().z;
			j["scaleX"] = (*it)->m_obj->GetScale().x;
			j["scaleY"] = (*it)->m_obj->GetScale().y;
			j["scaleZ"] = (*it)->m_obj->GetScale().z;
			j["rotX"] = (*it)->m_obj->GetRotate().x;
			j["rotY"] = (*it)->m_obj->GetRotate().y;
			j["rotZ"] = (*it)->m_obj->GetRotate().z;
			outFile << j.dump(m_mapList.size());
			it++;
			if(it!=m_gimmickList.end())
			outFile << ",";
		}
		outFile << "]";
		outFile.close();
		Application::Instance().m_log.AddLog("Save\n");
	}
}
