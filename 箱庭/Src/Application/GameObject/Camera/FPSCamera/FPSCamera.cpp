﻿#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 1.4f, 0.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//被写界深度	  
	//m_spCamera->SetFocus(
	//	m_mWorld.Translation().z,		// ピントの位置
	//	m_mWorld.Translation().z - 10,		//手前のぼかし距離
	//	m_mWorld.Translation().z + 10);		//奥のぼかし距離

	KdEffekseerManager::GetInstance().SetCamera(m_spCamera);
}

void FPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();	
	if (_spTarget)
	{
		_targetMat =Math::Matrix::CreateTranslation(_spTarget->GetMatrix().Translation());
		m_mLocalPos =Math::Matrix::CreateTranslation(_spTarget->GetCameraMatrix().Translation());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld	= m_mRotation * m_mLocalPos * _targetMat;

}
