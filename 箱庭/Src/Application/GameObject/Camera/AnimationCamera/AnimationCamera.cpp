#include "AnimationCamera.h"

#include"../../../Scene/SceneManager.h"

#include"../../../Scene/GameScene/GameScene.h"

void AnimationCamera::Update()
{
	std::shared_ptr<KdGameObject> _spStart = m_wpStart.lock();
	std::shared_ptr<KdGameObject> _spEnd = m_wpEnd.lock();

	if (!_spStart || !_spEnd)
	{
		//補間するための存在なので破棄 ※カメラ対象が不在になるのでフォロー必須
		m_isExpired = true;
		//途中破棄する場合はプレイヤーに戻すなど
		SceneManager::Instance().SetCameraTarget(m_wpEnd.lock());
		return;
	}

	//保管する行列の取得
	Math::Matrix _startMat = _spStart->GetCameraMatrix();
	Math::Matrix _endMat = _spEnd->GetCameraMatrix();

	//======================================
	//回転の補間
	//======================================
	
	Math::Quaternion _startQue;		//開始地点の回転
	Math::Quaternion _endQue;		//終了地点の回転
	Math::Quaternion _nowQue;		//現在地点の回転

	_startQue = Math::Quaternion::CreateFromRotationMatrix(_startMat);
	_endQue = Math::Quaternion::CreateFromRotationMatrix(_endMat);

	//進行具合を加味した回転を求める
	//球面線形補間
	_nowQue = Math::Quaternion::Slerp(_startQue, _endQue, m_progress);

	m_mWorld = Math::Matrix::CreateFromQuaternion(_nowQue);
	//======================================
	//回転の補間　ここまで
	//======================================
	
	//======================================
	//座標の補間
	//======================================
	
	//始点終点のベクトルの取得
	Math::Vector3 _startVec = _startMat.Translation();
	Math::Vector3 _endVec = _endMat.Translation()  ;

	//進行具合を加味した座標を求める
	Math::Vector3 _nowVec;

	//線形補間
	_nowVec = Math::Vector3::Lerp(_startVec, _endVec, m_progress);

	//ワールド行列を更新（座標）
	m_mWorld.Translation(_nowVec);

	//======================================
	//座標の補間　ここまで
	//======================================

	//======================================
	//進行具合の更新
	//======================================
	
	m_progress += m_speed;
	
	if (m_progress > 1.0f)
	{
		m_progress = 1.0f;
		//アニメーションが終了したら自身は消滅
		m_isExpired = true;
		
		std::shared_ptr<GameScene> _pNowScene = SceneManager::Instance().GetGameScene().lock();

		if (_pNowScene)
		{
			_pNowScene->SetCameraTarget(_spEnd);
		}

	}
}

void AnimationCamera::Init()
{
	//オブジェクト名
	m_objName = "AnimationCamera";
}

void AnimationCamera::SetAnimationInfo(const std::shared_ptr<KdGameObject>& start, const std::shared_ptr<KdGameObject>& end, float spd)
{
	
	//始点と終点を記憶
	m_wpStart = start;
	m_wpEnd = end;

	//進行度とスピードを初期化
	m_progress = 0.0f;
	m_speed = spd;
}
