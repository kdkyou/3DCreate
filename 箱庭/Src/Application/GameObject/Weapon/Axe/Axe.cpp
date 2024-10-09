#include "Axe.h"
#include"../../../Scene/SceneManager.h"
#include"../../Character/CharacterBase/CharacterBase.h"

void Axe::Update()
{
	//親(プレイヤー)の行列を取得
		const std::shared_ptr<const CharacterBase> _spParent = m_wpParent.lock();
		Math::Matrix _rotMat = Math::Matrix::Identity;
		static CharacterBase::SelectType _nowType = CharacterBase::SelectType::None;
		static CharacterBase::SelectType _nextType = CharacterBase::SelectType::None;

		if (_spParent)
		{
			const KdModelWork::Node* _pNode = _spParent->GetModelWork()->FindWorkNode("AttachPoint");
			if (_pNode)
			{
				m_parentAttachMat = _pNode->m_worldTransform;
			}

			if (!m_dirtyFlg)
			{
				_nextType = _spParent->GetNextType();
				if (_nowType != _nextType)
				{
					_nowType = _nextType;
					m_dirtyFlg = true;
				}

			}

			_parentMat = _spParent->GetMatrix();


		}


		if (m_dirtyFlg)
		{
			m_dirtyFlg = false;
			m_rotAng += HALF_AROUND;
			if (m_rotAng > 360)
			{
				m_rotAng -= 360;
			}

		}

		_rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotAng));

		m_mWorld = _rotMat * m_parentAttachMat * _parentMat;
}

void Axe::PostUpdate()
{

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;

	const std::shared_ptr<const CharacterBase> _spParent = m_wpParent.lock();
	if (_spParent)
	{
		Math::Matrix m_parentMat = _spParent->GetMatrix();

		const CharacterBase::SelectType _type = _spParent->GetType();

		if (_type==CharacterBase::SelectType::Break)
		{
			const KdModelWork::Node* _pNode = m_spWModel->FindWorkNode("BreakPoint");
			if (_pNode)
			{
				_sphereInfo.m_sphere.Center =((_pNode->m_worldTransform* m_parentAttachMat)*m_parentMat).Translation();
			}
			_sphereInfo.m_type = KdCollider::TypeDamage;

		}
		else if (_type == CharacterBase::SelectType::Push)
		{
			const KdModelWork::Node* _pNode = m_spWModel->FindWorkNode("PushPoint");
			if (_pNode)
			{
				_sphereInfo.m_sphere.Center = ((_pNode->m_worldTransform * m_parentAttachMat)* m_parentMat).Translation();
			}
			_sphereInfo.m_type = KdCollider::TypeEvent;

		}
		else
			return;

		_sphereInfo.m_sphere.Radius = m_scaleSize;

		if (_type == CharacterBase::SelectType::Break)
		{
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->Intersects(_sphereInfo, nullptr)) {
					obj->OnHit();
				}
			}
		}
		else if (_type == CharacterBase::SelectType::Push)
		{
			for (auto& obj : SceneManager::Instance().GetGimmickObjList())
			{
				if (obj->Intersects(_sphereInfo, nullptr)) {
					obj->OnHit();
				}
			}
		}
	}
}

void Axe::Init()
{
	m_spWModel = std::make_shared<KdModelWork>();
	m_spWModel->SetModelData("Asset/Models/Weapon/Axe/Axe.gltf");


	m_scaleSize = 0.1f;
	m_rotAng = 0.0f;
}

