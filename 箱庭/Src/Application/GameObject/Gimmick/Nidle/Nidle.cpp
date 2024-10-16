#include "Nidle.h"

void Nidle::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Nidle", m_spWkModel, KdCollider::TypeEvent | KdCollider::TypeDamage);

	m_spAnimator = std::make_shared<KdAnimator>();
	m_coolTime = 0;
}

void Nidle::Update()
{
	if (m_spAnimator->IsAnimationEnd())
	{
		m_coolTime--;
	}
	if (m_coolTime < 0)
	{
		m_coolTime = 0;
		m_isOnes = false;
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
	if (!m_isOnes)
	{
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Action"), false);
			m_isOnes = true;
			m_coolTime = COOL_TIME;
		}
	}
}
