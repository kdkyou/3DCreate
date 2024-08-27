#include "Cal.h"

void Cal::DrawLit()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Cal::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
}
