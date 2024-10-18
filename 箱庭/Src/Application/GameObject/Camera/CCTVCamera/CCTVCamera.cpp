#include "CCTVCamera.h"
#include"../../../Scene/SceneManager.h"

#include"../../Noise/Noise.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	m_pos = { -75.0f,75.0f,0.f };
	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);
	m_rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_rotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(320));
	// 一旦行列を確定させる
	m_mWorld	=m_rotY * m_rotZ * m_mLocalPos;

	m_tex= std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/GameObject/Apotheosis/Nyalrat1.png");


	KdEffekseerManager::GetInstance().SetCamera(m_spCamera);
}

void CCTVCamera::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON))m_flg = true;

	if (m_flg)
	{
		m_pos += {1.0f, -1.0f, 0.f};
		/*if (m_pos.x >= -2)
		{
		}
		else*/ 
		if (m_pos.x >= 2)
		{
			std::shared_ptr<Noise> noise = std::make_shared<Noise>();
			noise->SetParam(m_tex, 60, 15, kWhiteColor, false);
			SceneManager::Instance().AddNoise(noise);

			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
		KdEffekseerManager::GetInstance().Play("Baios.efkefc", m_pos, 1.0f, 2.0f,false);
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
