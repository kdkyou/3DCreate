#include "PitFall.h"

void PitFall::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PitFall", m_spWkModel, KdCollider::TypeGround | KdCollider::TypeEvent);

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Close"), false);

	
}

void PitFall::Init()
{
	m_type = InOut::None;
	m_coolTime = 0;
	m_coolFlg = false;
}

void PitFall::Update()
{
	if (m_type == InOut::None)
	{
		m_coolTime--;
		if (m_coolTime < 0)
		{
			m_coolTime = 0;
			m_coolFlg = false;
		}
	}
}

void PitFall::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void PitFall::OnEncount()
{
	switch (m_type)
	{
	case PitFall::None:
		if (!m_coolFlg)
		{
			if (m_spAnimator->IsAnimationEnd())
			{
				m_coolFlg = true;
				m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Open"), false);
				m_type = InOut::Open;
			}
		}
		break;
	case PitFall::Open:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Close"), false);
			m_type = InOut::Close;
		}
		break;
	case PitFall::Close:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_type = InOut::None;
			m_coolTime = RECAST_TIME;
		}
		break;
	default:
		break;
	}
}
