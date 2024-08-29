#include "Terrain.h"


void Terrain::Update()
{
	m_drawFlg = false;
}

void Terrain::GenerateDepthMapFromLight()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void Terrain::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
}

void Terrain::OnHit()
{
	m_drawFlg = true;
}

void Terrain::Release()
{
	m_spModel = nullptr;
}

