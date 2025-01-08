#include "ArrowBox.h"
#include"../../../Scene/SceneManager.h"

#include"../../Weapon/Arrow/Arrow.h"
#include"../../../AssetRepository/AssetRepository.h"

void ArrowBox::Init()
{
	m_nowPattern = Pattern::None;
	m_coolTime = 0;
	m_isOnes = false;
}

void ArrowBox::Update()
{
	m_coolTime-=Count;
	if (m_coolTime < 0)
	{
		m_coolTime = 0;
		m_isOnes = false;
	}

}

void ArrowBox::OnEncount()
{
	if (m_isOnes)return;
	
	  m_coolTime = COOL_TIME;
		m_isOnes = true;

		const  KdModelData::Node* _p1Node = m_spModel->FindNode("1");
		const  KdModelData::Node* _p2Node = m_spModel->FindNode("2");
		const  KdModelData::Node* _p3Node = m_spModel->FindNode("3");
		const  KdModelData::Node* _p4Node = m_spModel->FindNode("4");
		const  KdModelData::Node* _p5Node = m_spModel->FindNode("5");
		const  KdModelData::Node* _p6Node = m_spModel->FindNode("6");
		const  KdModelData::Node* _p7Node = m_spModel->FindNode("7");
		const  KdModelData::Node* _p8Node = m_spModel->FindNode("8");
		const  KdModelData::Node* _p9Node = m_spModel->FindNode("9");
		const  KdModelData::Node* _p10Node = m_spModel->FindNode("10");

		Math::Matrix one = Math::Matrix::Identity;
		Math::Matrix two = Math::Matrix::Identity;
		Math::Matrix three = Math::Matrix::Identity;
		Math::Matrix four = Math::Matrix::Identity;

		int num = m_random.GetInt(1, 5);
		switch (num)
		{
		case 1:
			m_nowPattern = ArrowBox::One;
			break;
		case 2:
			m_nowPattern = ArrowBox::Two;
			break;
		case 3:
			m_nowPattern = ArrowBox::Three;
			break;
		case 4:
			m_nowPattern = ArrowBox::Four;
			break;
		case 5:
			m_nowPattern = ArrowBox::Five;
			break;
		default:
			break;
		}

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
			three = _p6Node->m_worldTransform;
			four = _p4Node->m_worldTransform;
			break;
		default:
			break;
		}

		std::shared_ptr<Arrow> _arrow;
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->SetModel(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Arrow/Arrow.gltf"));
			_arrow->SetParam((one*m_mWorld ), one.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->SetModel(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Arrow/Arrow.gltf"));
			_arrow->SetParam((two * m_mWorld), two.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->SetModel(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Arrow/Arrow.gltf"));
			_arrow->SetParam((three * m_mWorld ), three.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}
		{
			_arrow = std::make_shared<Arrow>();
			_arrow->SetModel(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Arrow/Arrow.gltf"));
			_arrow->SetParam((four * m_mWorld), four.Backward(), 0.1f);
			SceneManager::Instance().AddObject(_arrow);
		}

}

void ArrowBox::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("ArrowBox", m_spModel,KdCollider::Type::TypeGround | KdCollider::TypeEvent );
}
