#include "Megaro.h"

void Megaro::Update()
{
	m_pos += m_move;

	if (m_pos.z>m_iniPos.z || m_pos.z<m_rimPos.z)
	{
		m_move *= -1;
		m_rot.y += 180;
		if (m_rot.y > 360)
		{
			m_rot.y -= 360;
		}
	}

	if (m_target)
	{
		KdCollider::SphereInfo _sphereInfo;

		_sphereInfo.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{ 0.f,0.5f,0.f };
		_sphereInfo.m_sphere.Radius = 3.0f;

		//m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kWhiteColor);

		//範囲内のオブジェクトの位置
		Math::Vector3 posDelta = m_target->GetPos() - m_mWorld.Translation();

		if (posDelta.Distance(m_target->GetPos(),m_mWorld.Translation())<_sphereInfo.m_sphere.Radius)
		{

			//現在の向いてる方向
			Math::Vector3 nowDir = m_mWorld.Backward();

			//範囲内オブジェクトの角度を算出
			float d = nowDir.Dot(posDelta);
			//丸め誤差使用
			d = std::clamp(d, -1.0f, 1.0f);
			//デグリー角に変更
			float targetAngle = DirectX::XMConvertToDegrees(acos(d));

			static float angle = 40;

			if (targetAngle < angle)
			{
				m_moveLevel = 2;
			}
			else
			{
				m_moveLevel = 1;
			}
		}
		else
		{
			m_moveLevel = 1;
		}
	}
		

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	m_mRotaion = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rot.y));

	m_mWorld = m_mRotaion * trans;
}

void Megaro::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Megaro", m_spModel, KdCollider::TypeEvent+KdCollider::TypeDamage);
}

void Megaro::SetPos(const Math::Vector3& pos)
{
	m_iniPos = pos;
	m_pos = pos;
	m_rimPos = { 82.0f,0.f,-51.f };
	m_move = (m_rimPos - m_iniPos) / MOVE_FRAME;
}

void Megaro::SetTarget(std::shared_ptr<KdGameObject> _target)
{
	m_target = _target;
}


