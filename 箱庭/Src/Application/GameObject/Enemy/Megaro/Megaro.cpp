#include "Megaro.h"

void Megaro::Update()
{
	m_pos += m_move;

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_mRotaion * trans;
}

void Megaro::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Megaro", m_spModel, KdCollider::TypeEvent+KdCollider::TypeDamage);
}

void Megaro::SetPos(const Math::Vector3& pos)
{
	m_iniPos = pos;
	m_rimPos = { -82.0f,0.f,-51.f };
	m_move = (m_rimPos - m_iniPos) / MOVE_FRAME;
}

void Megaro::SetTarget(std::shared_ptr<KdGameObject> _target)
{
	m_target = _target;
}


