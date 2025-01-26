#include "Light.h"
#include"../../../Scene/SceneManager.h"
#include"../../Character/CharacterBase/CharacterBase.h"

void Light::Update()
{
	//親(プレイヤー)の行列を取得
		const std::shared_ptr<const CharacterBase> _spParent = m_wpParent.lock();
		Math::Matrix _rotMat = Math::Matrix::Identity;
		Math::Matrix lightMat=Math::Matrix::Identity;

		if (_spParent)
		{
			const KdModelWork::Node* _pNode = _spParent->GetModelWork()->FindWorkNode("LightPoint");
			if (_pNode)
			{
				m_parentAttachMat = _pNode->m_worldTransform;
			}

			_parentMat = _spParent->GetMatrix();

			const KdModelWork::Node* _lNode = m_spWModel->FindWorkNode("LightPos");
			if (_pNode)
			{
				lightMat = _pNode->m_worldTransform;
			}
		}

		_rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotAng));

		m_mWorld = _rotMat * m_parentAttachMat * _parentMat;

		Math::Matrix mat = lightMat * m_mWorld;

		KdShaderManager::Instance().WorkAmbientController().SetConeLight(
			 mat.Translation(),
			m_mWorld.Forward(),
			10.0f,
			DirectX::XMConvertToRadians(40),
			Math::Vector3{ 1.0f,1.0f,1.0f } 
		);
}


void Light::Init()
{
	m_spWModel = std::make_shared<KdModelWork>();
	m_spWModel->SetModelData("Asset/Models/Weapon/Light/Light.gltf");


	m_rotAng = 180.0f;
}

