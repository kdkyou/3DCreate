#include "ArrowBox.h"
#include"../../../Scene/SceneManager.h"

#include"../../Weapon/Arrow/Arrow.h"
#include"../../../AssetRepository/AssetRepository.h"

void ArrowBox::Init()
{
	m_nowPattern = Pattern::None;
	m_cooltime = 0;
	m_shotflg = false;
}

void ArrowBox::Update()
{
	m_cooltime--;
	if (m_cooltime < 0)
	{
		m_cooltime = 0;
		m_shotflg = false;
	}
}

void ArrowBox::OnEncount()
{
	if (!m_shotflg)
	{
		m_cooltime = COOL_TIME;
		m_shotflg = true;

		const static KdModelData::Node* _p1Node = m_spModel->FindNode("1");
		const static KdModelData::Node* _p2Node = m_spModel->FindNode("2");
		const static KdModelData::Node* _p3Node = m_spModel->FindNode("3");
		const static KdModelData::Node* _p4Node = m_spModel->FindNode("4");
		const static KdModelData::Node* _p5Node = m_spModel->FindNode("5");
		const static KdModelData::Node* _p6Node = m_spModel->FindNode("6");
		const static KdModelData::Node* _p7Node = m_spModel->FindNode("7");
		const static KdModelData::Node* _p8Node = m_spModel->FindNode("8");
		const static KdModelData::Node* _p9Node = m_spModel->FindNode("9");
		const static KdModelData::Node* _p10Node = m_spModel->FindNode("10");

		Math::Matrix one;
		Math::Matrix two;
		Math::Matrix three;
		Math::Matrix four;

		m_nowPattern = Pattern::One;


		switch (m_nowPattern)
		{
		case ArrowBox::One:
			one = _p1Node->m_worldTransform;
			two = _p2Node->m_worldTransform;
			three = _p3Node->m_worldTransform;
			four = _p4Node->m_worldTransform;
			break;
		case ArrowBox::Two:
			one = _p5Node->m_worldTransform;
			two = _p6Node->m_worldTransform;
			three = _p9Node->m_worldTransform;
			four = _p3Node->m_worldTransform;
			break;
		case ArrowBox::Three:
			one = _p2Node->m_worldTransform;
			two = _p3Node->m_worldTransform;
			three = _p8Node->m_worldTransform;
			four = _p5Node->m_worldTransform;
			break;
		case ArrowBox::Four:
			one = _p4Node->m_worldTransform;
			two = _p7Node->m_worldTransform;
			three = _p10Node->m_worldTransform;
			four = _p1Node->m_worldTransform;
			break;
		case ArrowBox::Five:
			one = _p1Node->m_worldTransform;
			two = _p2Node->m_worldTransform;
			three = _p5Node->m_worldTransform;
			four = _p4Node->m_worldTransform;
			break;
		default:
			break;
		}

		std::shared_ptr<Arrow> _arrow;
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->Init();
			_arrow->SetModel(AssetRepository::Instance().GetModel("Arrow"));
			_arrow->SetParam((m_mWorld * one).Translation(), one.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->Init();
			_arrow->SetModel(AssetRepository::Instance().GetModel("Arrow"));
			_arrow->SetParam((m_mWorld * two).Translation(), two.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->Init();
			_arrow->SetModel(AssetRepository::Instance().GetModel("Arrow"));
			_arrow->SetParam((m_mWorld * three).Translation(), three.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->Init();
			_arrow->SetModel(AssetRepository::Instance().GetModel("Arrow"));
			_arrow->SetParam((m_mWorld * four).Translation(), four.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
	}

}

void ArrowBox::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("ArrowBox", m_spModel,KdCollider::Type::TypeGround | KdCollider::TypeEvent );

	
}
