#include "FallPillar.h"
#include"../../../Scene/SceneManager.h"

void FallPillar::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("FallPillar", m_spWkModel, KdCollider::Type::TypeGround | KdCollider::TypeEvent );

	m_spAnimator = std::make_shared<KdAnimator>();
}

void FallPillar::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void FallPillar::Update()
{
}

void FallPillar::PostUpdate()
{
	if (m_spAnimator)
	{
		m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
	}

	if (m_judgeFlg)
	{
		if (!m_spAnimator->IsAnimationEnd())
		{
			KdCollider::SphereInfo _sphereInfo;
			const KdModelWork::Node* _pNode = m_spWkModel->FindWorkNode("AttachPoint");
			if (_pNode)
			{
				_sphereInfo.m_sphere.Center = (_pNode->m_worldTransform * m_mWorld).Translation();
			}

			_sphereInfo.m_sphere.Radius = 1.f;
			_sphereInfo.m_type = KdCollider::TypeEvent;

			m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius);

			//ギミックリストの字面判定
			for (auto& obj : SceneManager::Instance().GetGimmickObjList())
			{
				if(obj->Intersects(_sphereInfo, nullptr))
				{
					obj->OnHit();
				}
			}
		}
	}

}

void FallPillar::OnHit()
{
	if (!m_isOnes)
	{
		m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Action"), false);
		m_isOnes = true;
		m_judgeFlg=true;
	}
}
