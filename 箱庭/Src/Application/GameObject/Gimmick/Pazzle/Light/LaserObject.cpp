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
		m_spTrail->SetEnable(false);
		return;
	}
	Math::Matrix trailMat;
	KdRandomGenerator randGen;
	int rand = randGen.GetInt(0, 1);
	if (rand == 0)
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
	rayInfo.m_type = KdCollider::TypeEvent;

	rayInfo.m_dir.Normalize();

	std::list<KdCollider::CollisionResult> results;

	std::list<std::weak_ptr<KdGameObject>> _obj;
	
	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(rayInfo, &results))
		{
			_obj.push_back(obj);
		}
	}

	Math::Vector3 pos = Math::Vector3::Zero;
	float		  maxOverLap = 0.0f;

	pos = rayInfo.m_pos + Math::Vector3(rayInfo.m_dir * rayInfo.m_range);

	//リスト内のオブジェクトをうごかす用イテレータ
	std::list<std::weak_ptr<KdGameObject>>::iterator it;
	//最終的に動かすオブジェクト
	std::weak_ptr<KdGameObject> ltObj;

	it = _obj.begin();

	for (auto& retList : results)
	{
		
		if (maxOverLap < retList.m_overlapDistance)
		{
			maxOverLap = retList.m_overlapDistance;
			pos = retList.m_hitPos;
			ltObj = it->lock();
		}
		++it;
	}
	_obj.clear();

	const std::shared_ptr<KdGameObject>t= ltObj.lock();
	if (t)
	{
		t->OnBright();
	}
	m_pos = pos;
	m_mlocalCamera = Math::Matrix::CreateTranslation(m_pos);
	
	m_isShot = true;
	m_isOnes = false;
	m_coolTime = COOL_TIME/2;
	if (!m_spTrail)return;
	m_spTrail->SetEnable(true);
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
	Math::Vector3 colr = { 0.61f,0.71f,0.61f };
	KdShaderManager::Instance().m_StandardShader.SetLimlightParam(colr, 0.6f);


	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.SetLimLightEnable(false);
}

void LaserObject::DrawUnLit()
{
	if (!m_spTrail)return;
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spTrail);
}


