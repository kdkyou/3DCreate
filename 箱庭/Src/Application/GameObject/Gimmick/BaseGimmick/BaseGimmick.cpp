#include "BaseGimmick.h"

void BaseGimmick::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mWorld);
	}
}

void BaseGimmick::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mWorld);
	}
}

void BaseGimmick::DrawBright()
{
	if (m_spModel)
	{
		if (m_brightTime > 0)
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
		}
	}

	if (m_spWkModel)
	{
		if (m_brightTime > 0)
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mWorld);
		}
	}
}

void BaseGimmick::OnBright()
{
	m_brightTime = BRIGHT_TIME;
}
