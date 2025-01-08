#include "DirectionSystem.h"
#include"../DirectionObject/DirectionObject.h"
#include"../../../../../Scene/SceneManager.h"

void DirectionSystem::Init()
{
	m_isOnes = false;

	std::shared_ptr<DirectionObject>dir;
//	for (int i = 0; i < 4; i++) 
	{
		dir = std::make_shared<DirectionObject>();
		dir->Init();
		SceneManager::Instance().AddGimmick(dir);
		m_objects.push_back(dir);
	}
}

void DirectionSystem::Update()
{
	if (!m_isOnes)return;

	for (const auto& obj : m_objects) {
		std::shared_ptr<DirectionObject> dirobj = obj.lock();
		if (!dirobj)continue;
		dirobj->OnBright();
	}
}

void DirectionSystem::OnHit()
{
	m_isOnes = true;
}

