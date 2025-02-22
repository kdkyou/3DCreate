﻿#include "CCTVCamera.h"
#include"../../../Scene/SceneManager.h"


#include"../../Fade/Fade.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	m_pos = { 0.0f,2.0f,-30.f };
	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);
	// 一旦行列を確定させる
	m_mWorld	=m_rotY * m_rotZ * m_mLocalPos;

	
	KdEffekseerManager::GetInstance().SetCamera(m_spCamera);
}

void CCTVCamera::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON))m_flg = true;

	if (m_flg)
	{
		m_pos += {0.0f, 0.f, 0.5f};
		
		if (m_pos.z >= 0)
		{
			std::shared_ptr<Fade>			_fade;
			_fade = std::make_shared<Fade>();
			_fade->Init();
			_fade->SetFade(Fade::FadeOut, 60, false);
			SceneManager::Instance().AddNoise(_fade);

			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
//		KdEffekseerManager::GetInstance().Play("Baios.efkefc", m_pos, 1.0f, 2.0f,false);
	}

	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotY * m_rotZ * m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{

}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	Math::Matrix _shadowVP =
		DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);

	m_mWorld = _shadowVP.Invert();
}
