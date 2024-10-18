#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
#include"../../GameObject/Texture/Texture.h"

void TitleScene::Init()
{
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	AddObject(_camera);


	std::shared_ptr<Texture>		_texture = std::make_shared<Texture>();
	_texture->Init();
	_texture->SetTexAlphaPos("Asset/Textures/GameObject/Title/title.png",false,{0,100});
	AddObject(_texture);

	_texture = std::make_shared<Texture>();
	_texture->Init();
	_texture->SetTexAlphaPos("Asset/Textures/GameObject/Relief/F.png",true,{0,-150});
	AddObject(_texture);

}

void TitleScene::Event()
{
	
}