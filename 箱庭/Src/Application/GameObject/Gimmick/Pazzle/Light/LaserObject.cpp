#include "LaserObject.h"
#include"../../../../Scene/SceneManager.h"

void LaserObject::Init()
{
	m_spTrail = std::make_shared<KdTrailPolygon>();
	m_spTrail->SetMaterial(KdAssets::Instance().m_textures.LoadData("Asset/Textures/GameObject/Trail/Light.png"));
	m_spTrail->SetLength(10);
	m_spTrail->SetColor(Math::Color{ 3.0f,3.0f,3.0f });
	m_spTrail->SetPattern(KdTrailPolygon::Trail_Pattern::eBillboard);
	m_spTrail->ClearPoints();

	m_angle = 0.0f;
	m_coolTime = 0;

	m_isOnes = false;
	m_isShot = false;
}

void LaserObject::Update()
{
	if (!m_isShot)return;

	m_coolTime--;
	if (m_coolTime < 0)
	{
		m_coolTime = 0;
		m_isShot = false;
		m_spTrail->ClearPoints();
		return;
	}
	Math::Matrix trailMat;
	if (m_coolTime % 2 == 0)
	{
		trailMat = m_mNpMat;
	}
	else
	{
		trailMat = m_mlocalCamera;
	}

	m_spTrail->AddPoint(trailMat);

	
}

void LaserObject::PostUpdate()
{
	if (!m_isOnes)	return;
	if (m_isShot)	return;


	KdCollider::RayInfo rayInfo;
	rayInfo.m_pos = m_mNpMat.Translation();
	rayInfo.m_dir = m_mNpMat.Backward();
	rayInfo.m_range = 10.0f;
	rayInfo.m_type = KdCollider::TypeGround | KdCollider::TypeEvent;

	rayInfo.m_dir.Normalize();

	std::list<KdCollider::CollisionResult> results;

	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(rayInfo, &results);
	}
	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(rayInfo, &results))
		{
			obj->OnBright();
		}
	}

	Math::Vector3 pos = Math::Vector3::Zero;
	float		  maxOverLap = 0.0f;

	pos = rayInfo.m_pos + Math::Vector3(rayInfo.m_dir * rayInfo.m_range);

	for (auto& retList : results)
	{
		if (maxOverLap < retList.m_overlapDistance)
		{
			maxOverLap = retList.m_overlapDistance;
			pos = retList.m_hitPos;
		}
	}

	m_pos = pos;
	m_mlocalCamera = Math::Matrix::CreateTranslation(m_pos);
	m_isShot = true;
	m_isOnes = false;
	m_coolTime = COOL_TIME;
}

void LaserObject::GenerateDepthMapFromLight()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void LaserObject::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.SetLimLightEnable(true);
	Math::Vector3 colr = { 0.21f,0.31f,0.21f };
	KdShaderManager::Instance().m_StandardShader.SetLimlightParam(colr, 0.5f);


	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.SetLimLightEnable(false);
}

void LaserObject::DrawUnLit()
{
	if (!m_spTrail)return;
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spTrail);
}


