#include "Arrow.h"

#include"../../../Scene/SceneManager.h"

void Arrow::Init()
{
	m_pos = {};
	m_moveDir = {};
	m_moveSpd = 0.f;
	m_aliveTime = 0;
	m_dissolve = 0.0f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Arrow::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spDModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Arrow", m_spDModel, KdCollider::TypeDamage);

	const KdModelData::Node* _pNode = m_spDModel->FindNode("AttachPoint");

	m_attach = _pNode->m_worldTransform;


}

void Arrow::Update()
{
	m_aliveTime--;
	if (m_aliveTime > 0)
	{
		m_pos += m_moveDir * m_moveSpd;
	}
	else
	{
		m_dissolveFlg = true;
	}

	if (m_dissolveFlg)
	{
		m_dissolve += 0.002f;
		if (m_dissolve > 1.0f)
		{
			m_isExpired = true;
		}
	}

	m_mWorld = m_rotMat * Math::Matrix::CreateTranslation(m_pos);
}

void Arrow::PostUpdate()
{
	KdCollider::SphereInfo _sphere;
	_sphere.m_sphere.Center = ( m_attach * m_mWorld).Translation();
	_sphere.m_sphere.Radius = 0.2f;
	_sphere.m_type = KdCollider::TypeGround;

	m_pDebugWire->AddDebugSphere(_sphere.m_sphere.Center, _sphere.m_sphere.Radius);

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphere, nullptr))
		{
			m_dissolveFlg = true;
		}
	}
}

void Arrow::DrawLit()
{
	if (m_dissolveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}
}

void Arrow::GenerateDepthMapFromLight()
{
	if (m_dissolveFlg)
	{
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}

}


void Arrow::SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _spd)
{
	m_pos = _pos;
	m_moveDir = _dir;
	m_moveDir.Normalize();
	m_moveSpd = _spd;
	m_aliveTime = ALIVE_TIME;

	//回転行列
	
	//現在の方向
	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();

	//向く方向
	Math::Vector3 _vecB = m_moveDir;
	_vecB.Normalize();

	float _dot = _vecA.Dot(_vecB);	//内積値算出
	float _angle = acos(_dot);		//内積で取得したcos値から2つのベクトルの角度算出

	//外積利用ベクトル(回転軸)作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);
	
	//角度分算出ベクトル(回転軸)で回転する行列を作成
	m_rotMat = Math::Matrix::CreateFromAxisAngle(_rotAxis, _angle);
}
