#include "SlideDoor.h"

#include"../../Dice/DiceManager.h"

#include"../../../AssetRepository/AssetRepository.h"
#include"../../../Scene/SceneManager.h"

void SlideDoor::Init()
{
	m_lrFlg = LR::None;
	m_isOnes = false;
	
	m_rightIniPos = { 0.0f,0.0f,8.0f };
	m_leftIniPos = { 0.0f,0.0f,-8.0f };

	m_speed = 0.01f;
	
	m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mRight = m_mRot * Math::Matrix::CreateTranslation(m_rightIniPos) ;
	m_mLeft = m_mRot * Math::Matrix::CreateTranslation(m_leftIniPos);
	
	m_spModel = AssetRepository::Instance().GetModel("BreakWall");
	m_spModelLeft = AssetRepository::Instance().GetModel("BreakWall");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("slide",{},2.0f, KdCollider::TypeEvent);

	m_pCollider->RegisterCollisionShape("DoorR", m_spModel,m_mRight, KdCollider::TypeGround);
	m_pCollider->RegisterCollisionShape("DoorL", m_spModelLeft,m_mLeft, KdCollider::TypeGround);
	
	m_mRight =m_mRight * m_mWorld;
	m_mLeft =m_mLeft * m_mWorld;



}

void SlideDoor::Update()
{
	if (m_lrFlg!=LR::None)
	{
		m_ang += 30.0f;
		if (m_ang > 360.0f)
		{
			m_ang -= 360.0f;
		}

		if (m_lrFlg == LR::Right)
		{
			if (m_rightPos.y < m_rightIniPos.y + RIMIT_HEIGHT)
			{
				m_rightPos.z = m_rightIniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
				m_rightPos.y += m_speed;
				m_mRight = m_mRot * Math::Matrix::CreateTranslation(m_rightPos) * m_mWorld;
			}
			else
			{
				m_lrFlg = LR::None;
				m_pCollider->SetEnable("DoorR", false);
			}
		}
		if (m_lrFlg == LR::Left)
		{
			if (m_leftPos.y < m_leftIniPos.y + RIMIT_HEIGHT)
			{
				m_leftPos.z = m_leftIniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
				m_leftPos.y += m_speed;
				m_mLeft = m_mRot * Math::Matrix::CreateTranslation(m_leftPos) * m_mWorld;
			}
			else
			{
				m_lrFlg = LR::None;
				m_pCollider->SetEnable("DoorL", false);

			}
		}
	}


	DiceManager::GetInstance().Update();
}

void SlideDoor::DrawUnLit()
{
	DiceManager::GetInstance().DrawUnLit();
}

void SlideDoor::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
	}
	if (m_spModelLeft)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelLeft, m_mLeft);
	}
}

void SlideDoor::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
	}
	if (m_spModelLeft)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelLeft, m_mLeft);
	}
}



void SlideDoor::OnEncount()
{
	if (m_isOnes)return;

		DiceManager::GetInstance().Ready(m_mWorld);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		bool flg = DiceManager::GetInstance().Dice(60);
		m_isOnes = true;
		if (flg)
		{
			m_lrFlg = LR::Right;
		}
		else
		{
			m_lrFlg = LR::Left;
		}
	}
}



