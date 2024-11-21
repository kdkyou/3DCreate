#include "ActerBase.h"

void ActerBase::DrawLit()
{
	if (!m_spModelWork)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);

}

void ActerBase::GenerateDepthMapFromLight()
{
	if (!m_spModelWork)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelWork, m_mWorld);
}
