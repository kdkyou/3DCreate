#include "RotateBridge.h"

void RotateBridge::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RotBridge", m_spWkModel, KdCollider::TypeGround);

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Action"));
}


void RotateBridge::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}


