#include "BreakWall.h"

void BreakWall::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("BreakWall", m_spWkModel, KdCollider::Type::TypeGround | KdCollider::TypeEvent );

	m_spAnimator = std::make_shared<KdAnimator>();
}

void BreakWall::Init()
{
	m_isOnes = false;
}


void BreakWall::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void BreakWall::OnHit()
{
	if (!m_isOnes)
	{
		m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Break"), false);
		m_isOnes = true;
	}
}
