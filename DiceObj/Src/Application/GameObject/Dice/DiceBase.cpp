#include "DiceBase.h"

#include"../Camera/TPSCamera/TPSCamera.h"


void DiceBase::Update()
{
	m_rot += m_rotDir;

	m_rotDir-={1,1,1};


	if (m_rot.x > 360)
	{
		m_rot.x -= 360;
	}
	else if (m_rot.x < 0)
	{
		m_rot.x += 360;
	}

	if (m_rot.y > 360)
	{
		m_rot.y -= 360;
	}
	else if (m_rot.y < 0)
	{
		m_rot.y += 360;
	}

	if (m_rot.z > 360)
	{
		m_rot.z -= 360;
	}
	else if (m_rot.z < 0)
	{
		m_rot.z += 360;
	}

	m_pos += m_moveDir * m_moveSpeed;

	if (m_moveSpeed > 0)
	{
		m_moveSpeed -= MOVE_DECREASE;
	}
	else
	{
		m_rotDir = {};
		m_moveDir = {};
	}
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
	/*if (!m_wpModel.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);
	}

	if (!m_wpModelWork.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModelWork.lock(), m_mWorld);
	}*/
}

void DiceBase::DrawUnLit()
{
	/*if (m_wpModel.expired())return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);*/
	
	if (!m_wpModel.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);
	}

	if (!m_wpModelWork.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModelWork.lock(), m_mWorld);
	}
	
}

void DiceBase::Release()
{
	
}

