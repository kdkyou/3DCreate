#include "Turret.h"

void Turret::Init()
{

	LaserObject::Init();

	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/RayserLight/Turret/Turret.gltf");

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

	Rotate();

	LaserObject::Update();

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle)) * trans;
	

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

void Turret::OnHit()
{
	if (m_isChange)return;
	m_isChange = true;
}

constexpr int ROTATE_ONCE_RIMIT = 90;
constexpr float ADD_ANGLE = 1.0f;

void Turret::Rotate()
{
	if (!m_isChange)return;

	static int spin = 0;

	//回転
	if (spin < ROTATE_ONCE_RIMIT)
	{
		//回転計測
		spin++;
		m_angle += ADD_ANGLE;
	}
	else
	{
		spin = 0;
		m_isChange = false;
//		KdEffekseerManager::GetInstance().Play("Mathes.efkefc", m_mWorld.Translation(), 0.2f, 1.3f, false);
	}

	if (m_angle > 360)
	{
		m_angle -= 360;
	}

}

