#include "ResultScene.h"

#include"../../GameObject/Enemy/Cal/Cal.h"
#include"../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

#include"../../GameObject/Fade/Fade.h"
#include"../../GameObject/Noise/Noise.h"

#include"../SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

void ResultScene::Init()
{
	std::shared_ptr<KdModelData>_model;
	Math::Matrix mat = Math::Matrix::CreateTranslation({ 100.f,-1.5f,0.f });
	_model = AssetRepository::Instance().GetModel("Cage");
	std::shared_ptr<Cal> _cal = std::make_shared<Cal>();
	_cal->SetMatrix(mat);
	_cal->SetModel(_model);
	AddObject(_cal);

	std::shared_ptr<Fade>			_fade;
	_fade = std::make_shared<Fade>();
	_fade->Init();
	_fade->SetFade(Fade::FadeIn, 40, false);
	m_objList.push_back(_fade);

	m_wpFade = _fade;

	std::shared_ptr<KdTexture> tex = std::make_shared<KdTexture>();
	tex->Load("Asset/Textures/GameObject/Apotheosis/End.png");

	std::shared_ptr<Noise> noise = std::make_shared<Noise>();
	noise->SetParam(tex, 120, 15, kWhiteColor, false);
	SceneManager::Instance().AddNoise(noise);


	//平行光(ディレクショナルライト)								↓方向			↓RGB
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0.f,-1,0.f }, { 0.3f,0.3f,0.3f });

	//環境光(アンビエントライト)											↓色RGBA　デフォルト0.3
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.4f, 0.4f, 0.4f, 1 });

	SceneManager::Instance().OffMapGimmick();
	KdAudioManager::Instance().StopAllSound();
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/babul.wav", true);

}

void ResultScene::Event()
{

	//フラグ
	static bool fadeFlg = false;
	
	m_frame++;
	if (m_frame >= TWO_SECOND)
	{
		if (!fadeFlg)
		{
			fadeFlg = true;
			std::shared_ptr<Fade> fade = m_wpFade.lock();
			if (fade)
			{
				fade->SetFade(Fade::FadeOut, 30, true);
			}
		}
		m_frame = 0;
	}
	
	if (fadeFlg)
	{
		if (!m_wpFade.expired())
		{
			if (m_wpFade.lock()->GetFillDisplay())
			{
				fadeFlg = false;
				SceneManager::Instance().SetNextScene(
					SceneManager::SceneType::Title
				);
				KdAudioManager::Instance().StopAllSound();
				KdEffekseerManager::GetInstance().StopAllEffect();
			}
		}
	}

}
