#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../GameObject/Camera/FreeCamera/FreeCamera.h"

void TitleScene::Init()
{
	std::shared_ptr<FreeCamera>		_camera = std::make_shared<FreeCamera>();
	_camera->Init();
	AddObject(_camera);
}

void TitleScene::Event()
{
	/*if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}*/
}