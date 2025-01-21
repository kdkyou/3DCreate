#include"CharacterBase.h"

void CharacterBase::DrawLit()
{
	if (!m_spModelWork)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);

}

void CharacterBase::GenerateDepthMapFromLight()
{
	if (!m_spModelWork)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);

}
