#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Character/Player/Character.h"

#include"../../GameObject/Gimmick/SlideDoor/SlideDoor.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"
#include"../../GameObject/Camera/AnimationCamera/AnimationCamera.h"

#include"../../GameObject/Gimmick/Gate/Gate.h"
#include"../../GameObject/Gimmick/Granite/Granite.h"

#include"../../GameObject/Weapon/Light/Light.h"

#include"../../AssetRepository/AssetRepository.h"

#include"../../GameObject/Dice/DiceManager.h"

#include"../../GameObject/Fade/Fade.h"

#include"../../GameObject/Noise/Noise.h"


bool GameScene::SetCameraTarget(std::weak_ptr<KdGameObject> target)
{
	std::shared_ptr<KdGameObject> _target = target.lock();
	if (_target)
	{
		std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
		if (_spCamera)
		{
			_spCamera->SetTarget(_target);
		}
		//ターゲットの名前を更新
		m_strCameraTarget = _target->GetObjName();
		return true;
	}

	return false;
}


void GameScene::ChangeCameraTarget()
{
	//アニメーション中は切り替えない!!
	std::shared_ptr<KdGameObject> _anim;
	_anim = FindObjectWithName("AnimationCamera");
	if (_anim)return;

	//今のターゲットを探す
	std::shared_ptr<KdGameObject> _now = FindObjectWithName(m_strCameraTarget);
	if (!_now)return;

	//新しいターゲットの名前を設定  ※効率最悪なので真似しない
	m_strCameraTarget = "Player";
	


	//新しいターゲットを検索
	std::shared_ptr<KdGameObject> _target = FindObjectWithName(m_strCameraTarget);
	if (!_target)return;

	
	//補完用のオブジェクトを作成

	//保管用のオブジェクトをカメラのターゲットに切り替える

	std::shared_ptr<AnimationCamera> _animCamera;
	_animCamera = std::make_shared<AnimationCamera>();
	_animCamera->Init();
	_animCamera->SetAnimationInfo( _now, _target);
	_animCamera->Update();
	m_objList.push_back(_animCamera);
	std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{

		_spCamera->SetTarget(_animCamera);
	}
}


void GameScene::Init()
{

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->SetPlayer(_character);
	_character->Init();
	AddObject(_character);

	//===================================================================	
	// 持ち物初期化
	//===================================================================
	std::shared_ptr<Light> _axe = std::make_shared<Light>();
	_axe->Init();
	_axe->SetParent(_character);
	AddObject(_axe);

	std::shared_ptr<Granite> gra = std::make_shared<Granite>();
	gra->Init();
	AddObject(gra);
	

	//ゴール
	std::shared_ptr<Gate> _gate = std::make_shared<Gate>();
	_gate->Init();
	AddObject(_gate);


	//===================================================================
	// カメラ初期化
	//===================================================================
//	std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<FPSCamera>			_camera = std::make_shared<FPSCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_character->SetCamera(_camera);
	AddObject(_camera);

	m_wpCamera = _camera;


	ChangeCameraTarget();

	std::shared_ptr<Fade>			_fade;
	_fade = std::make_shared<Fade>();
	_fade->Init();
	_fade->SetFade(Fade::FadeIn, 40, false);
	m_objList.push_back(_fade);

	m_tex=KdAssets::Instance().m_textures.GetData("Asset/Textures/GameObject/Apotheosis/Nyalrat1.png");


	DiceManager::GetInstance().SetCamera(_camera);
	
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/R'lyeh.wav", true);
}


std::shared_ptr<KdGameObject> GameScene::FindObjectWithName(const std::string& name)
{
	if (m_objList.empty())return nullptr;

	for (auto& obj : m_objList)
	{
		//文字列比較
		if (obj->GetObjName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

void GameScene::Event()
{
	if (GetAsyncKeyState('T'))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
		KdAudioManager::Instance().StopAllSound();
	}
	if (GetAsyncKeyState('P'))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		KdAudioManager::Instance().StopAllSound();
	}
}
