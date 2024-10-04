#include "RotateBridge.h"

void RotateBridge::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RotBridge", m_spModel, KdCollider::TypeGround);

	const static KdModelData::Node* _p1Node = m_spModel->FindNode("GearP");
	if (_p1Node)
	{
		m_mGear = m_mWorld * _p1Node->m_worldTransform;
	}
}

void RotateBridge::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	
	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Rotate"));
}

void RotateBridge::Init()
{
	m_ang = 0;
	m_spin = 0;
}

void RotateBridge::Update()
{

}


void RotateBridge::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void RotateBridge::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mGear);
	}
}

void RotateBridge::DrawLit()
{

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mGear);
	}
}


