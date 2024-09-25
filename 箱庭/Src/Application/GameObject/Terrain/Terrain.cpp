#include "Terrain.h"


void Terrain::Update()
{
	m_drawFlg = false;
}

void Terrain::GenerateDepthMapFromLight()
{
	if (!m_spModel) return;
//	if (!m_drawFlg)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;
//	if (!m_drawFlg)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void Terrain::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
	DirectX::BoundingBox _box;
	_box.Center = m_mWorld.Translation();
	_box.Extents = { 5,5,5 };
//	m_pCollider->RegisterCollisionShape("Ground",_box, KdCollider::TypeGround);
//	m_pCollider->RegisterCollisionShape("Ground",{1,1,1},1, KdCollider::TypeGround);


}

void Terrain::OnHit()
{
	//m_drawFlg = true;
}

void Terrain::Release()
{
	m_spModel = nullptr;
}

