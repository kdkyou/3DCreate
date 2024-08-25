#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include"MapScene/MapScene.h"
#include"GimmickScene/GimmickScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
	if (m_MapObjFlg)
	{
		m_gimmickScene->PreUpdate();
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();
	if (m_MapObjFlg)
	{
		m_gimmickScene->Update();
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
	if (m_MapObjFlg)
	{
		m_gimmickScene->PreDraw();
	}
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
	if (m_MapObjFlg)
	{
		m_mapScene->Draw();
		m_gimmickScene->Draw();
	}
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
	if (m_MapObjFlg)
	{
		m_gimmickScene->DrawSprite();
	}
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
		m_MapObjFlg = false;
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		m_MapObjFlg = true;
		break;
	}

	if (!m_mapScene)m_mapScene = std::make_shared<MapScene>();
	if (!m_gimmickScene)m_gimmickScene = std::make_shared<GimmickScene>();

	// 現在のシーン情報を更新
	m_currentSceneType = sceneType;
}
