#include "Nidle.h"

void Nidle::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Nidle", m_spWkModel, KdCollider::TypeEvent | KdCollider::TypeDamage);

	m_spAnimator = std::make_shared<KdAnimator>();
}

void Nidle::Update()
{
	m_brightTime--;
	if (m_brightTime < 0)
	{
		m_brightTime = 0;
	}
}

void Nidle::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void Nidle::OnHit()
{
}

void Nidle::OnEncount()
{
	if(m_spAnimator->IsAnimationEnd())
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Action"),false);
}
