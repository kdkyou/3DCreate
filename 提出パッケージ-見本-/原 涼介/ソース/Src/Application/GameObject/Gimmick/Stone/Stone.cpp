#include "Stone.h"

#include"../../../Scene/SceneManager.h"


void Stone::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Stone::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Stone", m_spModel, KdCollider::TypeDamage);

	/*m_trail = std::make_shared<KdTrailPolygon>();
	m_trail->SetMaterial("Asset/Textures/GameObject/Trail/Babul.png");*/

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
			if (m_trail)
			{
				m_trail->AddPoint(_mat);
			}
		}
	}
	else
	{
		if (m_trail)
		{
			m_trail->ClearPoints();
		}
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
	KdEffekseerManager::GetInstance().Play("Babul.efkefc", m_pos, 0.1f, 2.0f, nullptr, false);

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
	static Math::Vector2 offset = { 0.0f,0.0f };
	offset.x += WATER_SPEED;
	offset.y += WATER_SPEED;
	if (offset.x > 1.0f)
	{
		offset.x -= 1.0f;
	}
	if (offset.y > 1.0f)
	{
		offset.x -= 1.0f;
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterUVOffset(offset);

	//板ポリに張るテクスチャの数を増やす
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 4,4 });

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);

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


