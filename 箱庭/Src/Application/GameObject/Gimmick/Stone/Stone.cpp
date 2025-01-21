#include "Stone.h"

#include"../../../Scene/SceneManager.h"


void Stone::Init()
{
	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Stone/Stone.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Stone", m_spModel, KdCollider::TypeDamage);
}

void Stone::SetModel(const std::shared_ptr<KdModelData>& model)
{
}

void Stone::Update()
{
	m_aliveTime--;
	if (m_aliveTime > 0)
	{
		m_pos += m_moveDir * m_moveSpd;
		{
			Math::Matrix _mat;
			_mat.Translation(m_pos);
		
		}

		KdEffekseerManager::GetInstance().Play("Babul.efkefc", m_pos, 0.1f, 2.0f, nullptr, false);
	}
	else
	{

		m_dissolveFlg = true;
	}

	if (m_dissolveFlg)
	{
		m_dissolve += 0.005f;
		if (m_dissolve > 1.0f)
		{
			m_isExpired = true;
		}
	}

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Stone::PostUpdate()
{
	KdCollider::SphereInfo _sphere;
	_sphere.m_sphere.Center = m_mWorld.Translation();
	_sphere.m_sphere.Radius = 0.2f;
	_sphere.m_type = KdCollider::TypeGround;

	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		if (obj->Intersects(_sphere, nullptr))
		{
			OnHit();
		}
	}
}

void Stone::DrawLit()
{
	if (m_dissolveFlg)
	{
		Math::Vector3 _colr(0.2f, 0.2f, 0.25f);
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, nullptr, &_colr);
	}

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}

	if (m_trail)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_trail);
	}
}

void Stone::GenerateDepthMapFromLight()
{
	if (m_dissolveFlg)
	{
		Math::Vector3 _colr(0.2f, 0.2f, 0.25f);
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, nullptr, &_colr);
	}

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}

	if (m_trail)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_trail);
	}
}


void Stone::SetParam(const Math::Matrix& _mat, const Math::Vector3& _dir, float _spd)
{
	m_mWorld = _mat;
	m_pos = _mat.Translation();
	m_moveDir = _dir;
	m_moveDir.Normalize();
	m_moveSpd = _spd;
	m_aliveTime = ALIVE_TIME;
	m_dissolve = 0.0f;


}

void Stone::OnHit()
{
	m_aliveTime = 0;
	m_pCollider->SetEnable("Stone", false);
}


