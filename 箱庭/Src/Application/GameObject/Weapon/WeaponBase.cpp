#include "WeaponBase.h"
#include"../Character/CharacterBase/CharacterBase.h"

void WeaponBase::DrawLit()
{
	if (m_spWModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWModel, m_mWorld);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}

}

void WeaponBase::GenerateDepthMapFromLight()
{
	if (m_spWModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWModel, m_mWorld);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}
}


