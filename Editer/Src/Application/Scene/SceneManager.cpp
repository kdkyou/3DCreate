#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

#include"../main.h"

#include"magic_enum.hpp"

#include"../GameObject/Test.h"
#include"../AssetRepository/AssetRepository.h"

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
	

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::Button("Save"))	{
				SaveMap();
			}
			ImGui::EndMenu();
		}
			ImGui::EndMenuBar();
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
		if (ImGui::Button("Normal"))
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
	}
	
	ImGui::Text("pos");
	if (ImGui::Button("PosReset"))
	{
		m_pos = {};
	}
	ImGui::SliderFloat("pos.x", &m_pos.x, -300, 300);
	ImGui::SliderFloat("pos.y", &m_pos.y, -300, 300);
	ImGui::SliderFloat("pos.z", &m_pos.z, -300, 300);

	ImGui::Text("scale");
	if (ImGui::Button("ScaleReset"))
	{
		m_scale = {1,1,1};
	}
	ImGui::SliderFloat("scale.x", &m_scale.x, 0.1f, 10.0f);
	ImGui::SliderFloat("scale.y", &m_scale.y, 0.1f, 10.0f);
	ImGui::SliderFloat("scale.z", &m_scale.z, 0.1f, 10.0f);

	ImGui::Text("rotate");
	if (ImGui::Button("RotateReset"))
	{
		m_rot = {};
	}
	ImGui::SliderAngle("rotate.x", &m_rot.x);
	ImGui::SliderAngle("rotate.y", &m_rot.y);
	ImGui::SliderAngle("rotate.z", &m_rot.z);

	if (m_spNow != nullptr)
	{
		Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
		Math::Matrix _scale = Math::Matrix::CreateScale(m_scale);
		Math::Matrix _rotX = Math::Matrix::CreateRotationX(m_rot.x);
		Math::Matrix _rotY = Math::Matrix::CreateRotationY(m_rot.y);
		Math::Matrix _rotZ = Math::Matrix::CreateRotationZ(m_rot.z);
		Math::Matrix _mat = _scale * _rotX*_rotY*_rotZ * _trans;
		m_spNow->SetMatrix(_mat);
	}

	

	

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
