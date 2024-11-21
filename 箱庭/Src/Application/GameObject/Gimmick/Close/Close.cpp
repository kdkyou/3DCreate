#include "Close.h"

void Close::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model; 
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_spModel, KdCollider::TypeGround);
}

void Close::Update()
{
	if (m_isOnes)
	{
		m_pos.y -=0.0001f ;

		m_mWorld = Math::Matrix::CreateTranslation(m_pos);
	}
}
