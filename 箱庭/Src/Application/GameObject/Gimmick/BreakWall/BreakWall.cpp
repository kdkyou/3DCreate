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
	/*m_spWkModel = std::make_shared<KdModelWork>();
	m_spWkModel->SetModelData("Asset/Models/Terrains/Gimmick/BreakWall/BreakWall.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_spWkModel, KdCollider::TypeEvent | KdCollider::Type::TypeGround);

	m_spAnimator = std::make_shared<KdAnimator>();*/
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
