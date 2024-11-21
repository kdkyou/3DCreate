#include "PitFall.h"

#include"../Stone/Stone.h"
#include"../../../Scene/SceneManager.h"

#include"../../../AssetRepository/AssetRepository.h"

void PitFall::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PitFall", m_spWkModel, KdCollider::TypeGround | KdCollider::TypeEvent);

	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Close"), false);

	
}

void PitFall::Init()
{
	m_type = OpenClose::None;
	m_coolTime = 0;
	m_coolFlg = false;
	m_stoneCool = 0;
}

void PitFall::Update()
{
	if (m_type == OpenClose::None)
	{
		m_coolTime--;
		if (m_coolTime < 0)
		{
			m_coolTime = 0;
			m_coolFlg = false;
		}
	}
	else if (m_type == OpenClose::Open)
	{
		m_stoneCool--;
		if (m_stoneCool < 0)
		{
			CreateStone();
			m_stoneCool = CREATE_CAST;
		}
		if (m_spAnimator->IsAnimationEnd())
		{
			m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Close"), false);
			m_type = OpenClose::Close;
		}
	}
}

void PitFall::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void PitFall::OnEncount()
{
	switch (m_type)
	{
	case PitFall::None:
		if (!m_coolFlg)
		{
			if (m_spAnimator->IsAnimationEnd())
			{
				m_coolFlg = true;
				m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Open"), false);
				m_type = OpenClose::Open;
			}
		}
		break;
	case PitFall::Close:
		if (m_spAnimator->IsAnimationEnd())
		{
			m_type = OpenClose::None;
			m_coolTime = RECAST_TIME;
		}
		break;
	default:
		break;
	}
}

void PitFall::CreateStone()
{
	std::shared_ptr<Stone> stone = std::make_shared<Stone>();
	stone->SetModel(AssetRepository::Instance().GetModel("Stone"));
	Math::Vector3 pos = Math::Vector3{ randGene.GetFloat(-3.0f,3.0f),0.0f,randGene.GetFloat(-3.0f,3.0f) };
	Math::Matrix mat = Math::Matrix::CreateTranslation(pos) * m_mWorld;
	stone->SetParam(mat, Math::Vector3::Down, randGene.GetFloat(0.05f, 0.3f));
	SceneManager::Instance().AddObject(stone);
}
