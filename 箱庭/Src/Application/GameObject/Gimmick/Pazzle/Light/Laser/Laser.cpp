#include"Laser.h"

void Laser::Init()
{
	LaserObject::Init();


	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/RayserLight/Rayser/Rayser.gltf");

	const  KdModelData::Node* _pNode = m_spModel->FindNode("ShotPoint");
	if (_pNode)
	{
		m_mNpMat = _pNode->m_worldTransform * m_mWorld;
	}

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Laser", m_spModel, KdCollider::TypeGround | KdCollider::TypeEvent);

}

void Laser::Update()
{
	LaserObject::Update();
	/*Math::Matrix trans =Math::Matrix::CreateTranslation(m_mWorld.Translation());
	m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle)) * trans;*/
}

void Laser::PostUpdate()
{
	const  KdModelData::Node* _pNode = m_spModel->FindNode("ShotPoint");
	if (_pNode)
	{
		m_mNpMat = _pNode->m_worldTransform * m_mWorld;
	}

	LaserObject::PostUpdate();
}

void Laser::OnHit()
{
	if (m_isOnes)return;
	m_isOnes = true;
}