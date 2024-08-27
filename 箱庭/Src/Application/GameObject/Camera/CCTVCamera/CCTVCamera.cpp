#include "CCTVCamera.h"
#include"../../../Scene/SceneManager.h"

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
}

void CCTVCamera::Update()
{
	if (GetAsyncKeyState('F'))m_flg = true;

	if (m_flg)
	{
		m_pos += {1.0f, -1.0f, 0.f};
		if (m_pos.x >= 2)
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
	}

	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotY * m_rotZ * m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	/*Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}*/

	// カメラの回転
	//UpdateLookAtRotate(_targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	Math::Matrix _shadowVP =
		DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);

	m_mWorld = _shadowVP.Invert();
}
