#include "Turret.h"

void Turret::Init()
{

	LaserObject::Init();

	m_spModel=KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/RayserLight/Turret/Turret.gltf");

	const  KdModelData::Node* _pNode = m_spModel->FindNode("ShotPoint");
	if (_pNode)
	{
		m_mNpMat = _pNode->m_worldTransform * m_mWorld;
	}

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Turret", m_spModel, KdCollider::TypeGround | KdCollider::TypeEvent);

}

void Turret::Update()
{
	LaserObject::Update();
}

void Turret::PostUpdate()
{
	const  KdModelData::Node* _pNode = m_spModel->FindNode("ShotPoint");
	if (_pNode)
	{
		m_mNpMat = _pNode->m_worldTransform * m_mWorld;
	}

	LaserObject::PostUpdate();
}

void Turret::OnBright()
{
	if (m_isOnes)return;
	m_isOnes = true;
}
