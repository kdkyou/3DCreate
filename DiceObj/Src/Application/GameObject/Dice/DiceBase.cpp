#include "DiceBase.h"

#include"../Camera/TPSCamera/TPSCamera.h"


void DiceBase::Update()
{
	m_rot += m_rotDir;

	m_rotDir-={1,1,1};


	if (m_rot.x > ONE_AROUND)
	{
		m_rot.x -= ONE_AROUND;
	}
	else if (m_rot.x < 0)
	{
		m_rot.x += ONE_AROUND;
	}

	if (m_rot.y > ONE_AROUND)
	{
		m_rot.y -= ONE_AROUND;
	}
	else if (m_rot.y < 0)
	{
		m_rot.y += ONE_AROUND;
	}

	if (m_rot.z > ONE_AROUND)
	{
		m_rot.z -= ONE_AROUND;
	}
	else if (m_rot.z < 0)
	{
		m_rot.z += ONE_AROUND;
	}

	m_pos += m_moveDir * m_moveSpeed;

	if (m_moveSpeed > 0)
	{
		m_moveSpeed -= MOVE_DECREASE;
	}
	else
	{
		//m_showFrame--;

		m_rotDir = {};
		m_moveDir = {};
	}

	/*if (m_showFrame < 0)
	{
		m_isExpired = true;
	}*/
}

void DiceBase::PostUpdate()
{
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	if (!m_wpCamera.expired())
	{
		_targetMat = m_wpCamera.lock()->GetMatrix();
	}

	m_mRotMat = Math::Matrix::CreateFromYawPitchRoll(m_rot);
	m_mTransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_mScaleMat * m_mRotMat * m_mTransMat*_targetMat;
}

void DiceBase::DrawBright()
{
	/*if (m_wpModel.expired())return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);*/
}

void DiceBase::DrawUnLit()
{
	if (m_wpModel.expired())return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);
	
}

void DiceBase::Release()
{
	
}

