#include "Door.h"

void Door::Update()
{
	
	if (m_isOnes)
	{
		m_ang += 30;
		if (m_ang > 360)
		{
			m_ang -= 360;
		}

		if (m_pos.y < m_iniPos.y+ RIMIT_HEIGHT)
		{
			m_pos.z = m_iniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
			m_pos.y += m_speed;
			m_mWorld = Math::Matrix::CreateTranslation(m_pos);
		}
	}
}

void Door::SetParam(const Math::Matrix& mat)
{
	m_mWorld = mat;
	m_iniPos = mat.Translation();
	m_speed = 0.01f;

}

void Door::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Slide", m_spModel, KdCollider::TypeGround);
}

void Door::Start()
{
	m_isOnes = true;
}
