#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include"MapScene/MapScene.h"
#include"GimmickScene/GimmickScene.h"
#include"DiceScene/DiceScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_diceScene->PreUpdate();
	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	if (m_diceFlg)
	{
		m_diceScene->Update();
	}
	else
	{
		m_currentScene->Update();
		if (m_MapObjFlg)
		{
			m_gimmickScene->Update();
		}
	}
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
	if (m_MapObjFlg)
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
	if (m_MapObjFlg)
	{
		m_mapScene->Draw();
		m_gimmickScene->Draw();
	}
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	
	if (m_nextSceneType == SceneManager::SceneType::Game)
	{
		m_diceScene->DrawSprite();
	}
	m_gimmickScene->DrawSprite();
	m_currentScene->DrawSprite();

}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
	if (m_MapObjFlg)
	{
		m_gimmickScene->DrawDebug();
	}
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

void SceneManager::DiceFlgONOFF(bool OnOff)
{
	m_diceFlg = OnOff;
}




void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& obj)
{
	m_currentScene->AddObject(obj);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		m_MapObjFlg = true;
		m_gimmickScene = nullptr;
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		m_MapObjFlg = true;
		break;
	}

	if (!m_mapScene)m_mapScene = std::make_shared<MapScene>();
	if (!m_gimmickScene)m_gimmickScene = std::make_shared<GimmickScene>();
	if (!m_diceScene)m_diceScene = std::make_shared<DiceScene>();

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}
