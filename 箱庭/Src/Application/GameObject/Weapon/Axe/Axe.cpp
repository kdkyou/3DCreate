#include "Axe.h"
#include"../../../Scene/SceneManager.h"
#include"../../Character/CharacterBase/CharacterBase.h"

void Axe::Update()
{
	//親(プレイヤー)の行列を取得
		const std::shared_ptr<const CharacterBase> _wpParent = m_wpParent.lock();
		
		if (_wpParent)
		{
			const KdModelWork::Node* _pNode = _wpParent->GetModelWork()->FindWorkNode("AttachPoint");
			if (_pNode)
			{
				m_parentAttachMat = _pNode->m_worldTransform;
			}

			_parentMat = _wpParent->GetMatrix();
		}

		m_mWorld = m_parentAttachMat*_parentMat;	
}

void Axe::PostUpdate()
{

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;		//	当たっていたらtrue

	const std::shared_ptr<const CharacterBase> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		Math::Matrix m_parentMat = _spParent->GetMatrix();
		if (_spParent->GetType()==CharacterBase::SelectType::Break)
		{
			const KdModelWork::Node* _pNode = m_spWModel->FindWorkNode("BreakPoint");
			if (_pNode)
			{
				_sphereInfo.m_sphere.Center =((_pNode->m_worldTransform* m_parentAttachMat)*m_parentMat).Translation();
			}
		}
		else if (_spParent->GetType() == CharacterBase::SelectType::Push)
		{
			const KdModelWork::Node* _pNode = m_spWModel->FindWorkNode("PushPoint");
			if (_pNode)
			{
				_sphereInfo.m_sphere.Center = ((_pNode->m_worldTransform * m_parentAttachMat
					)* m_parentMat).Translation();
			}
		}
		else
			return;

		_sphereInfo.m_sphere.Radius = m_scaleSize;
	}

	_sphereInfo.m_type = KdCollider::TypeEvent;

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr)) {
			obj->OnHit();
		}
	}
}

void Axe::Init()
{
	m_spWModel = std::make_shared<KdModelWork>();
	m_spWModel->SetModelData("Asset/Models/Weapon/Axe/Axe.gltf");


	m_scaleSize = 0.1f;
}

