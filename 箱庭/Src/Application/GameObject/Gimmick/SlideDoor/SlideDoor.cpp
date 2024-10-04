#include "SlideDoor.h"

#include"../../Dice/DiceManager.h"

void SlideDoor::Init()
{
	m_lrFlg = LR::None;
	m_speed = 0.01f;
	m_left = { 0,0,-8 };
	m_right = { 0,0,8 };
	m_mLeft = m_mWorld * Math::Matrix::CreateTranslation(m_left);
	m_mRight = m_mWorld * Math::Matrix::CreateTranslation(m_right);
}

void SlideDoor::Update()
{
	m_ang += 30;
	if (m_ang > 360)
	{
		m_ang -= 360;
	}
	if (m_lrFlg == LR::Right)
	{
		m_right.z = 8 + sin(DirectX::XMConvertToRadians(m_ang))*0.1f;
		m_right.y += m_speed;
		m_mRight = m_mWorld * Math::Matrix::CreateTranslation(m_right);
	}
	if (m_lrFlg == LR::Left)
	{
		m_left.z = -8 +sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
		m_left.y += m_speed;
		m_mLeft = m_mWorld * Math::Matrix::CreateTranslation(m_left);
	}
	if (m_left.y > RIMIT_HEIGHT || m_right.y > RIMIT_HEIGHT)
	{
		m_lrFlg = LR::None;
	}

	DiceManager::GetInstance().Update();
}

void SlideDoor::PostUpdate()
{

}

void SlideDoor::DrawUnLit()
{
	DiceManager::GetInstance().DrawUnLit();
}

void SlideDoor::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mLeft);
	}
}

void SlideDoor::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mLeft);
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

void SlideDoor::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Slide", m_spModel, KdCollider::TypeGround | KdCollider::TypeEvent);
}
