#include "DiceBase.h"

void DiceBase::DrawBright()
{
	if (!m_wpModel.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModel.lock(), m_mWorld);
	}

	if (!m_wpModelWork.expired())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_wpModelWork.lock(), m_mWorld);
	}
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

