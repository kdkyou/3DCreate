#include "Nidle.h"

void Nidle::SetModel(std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Relief", m_spWkModel, KdCollider::TypeEvent+KdCollider::TypeDamage);

	m_spAnimetor = std::make_shared<KdAnimator>();
}

void Nidle::Update()
{
}

void Nidle::PostUpdate()
{
	m_spAnimetor->AdvanceTime(m_spWkModel->WorkNodes());
}

void Nidle::OnHit()
{
}

void Nidle::OnEncount()
{
	if(m_spAnimetor->IsAnimationEnd())
	m_spAnimetor->SetAnimation(m_spWkModel->GetAnimation("Action"),false);
}
