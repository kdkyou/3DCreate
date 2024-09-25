#include "Wall.h"

void Wall::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_spWkModel, KdCollider::TypeEvent | KdCollider::TypeDamage);

	m_spAnimator = std::make_shared<KdAnimator>();
}

void Wall::Init()
{
	m_spWkModel = std::make_shared<KdModelWork>();
	m_spWkModel->SetModelData("Asset/Models/Terrains/Gimmick/Wall/Wall.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_spWkModel, KdCollider::TypeEvent | KdCollider::TypeDamage);

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("CloseOut"), false);
	m_type = InOut::None;
}

void Wall::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}


void Wall::OnEncount()
{
	
	switch (m_type)
	{
	case Wall::None:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("CloseIn"), false);
			m_type = InOut::In;
		}
		break;
	case Wall::In:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("CloseOut"), false);
			m_type = InOut::Out;
		}
		break;
	case Wall::Out:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_type = InOut::None;
		}
		break;
	default:
		break;
	}
}
