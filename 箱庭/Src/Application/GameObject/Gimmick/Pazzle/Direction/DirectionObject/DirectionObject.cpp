#include "DirectionObject.h"

void DirectionObject::Init()
{
	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/RayserLight/Turret/Turret.gltf");

	m_mWorld.Translation({ 0,1,0 });
}

void DirectionObject::Update()
{
	if (!m_isOnes) return;

	m_angle += AddCount;

	if (m_angle > 360) {
		m_angle -= 360;
	}
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	Math::Matrix rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	m_mWorld = rotYMat * transMat;
}

void DirectionObject::OnBright()
{
	m_isOnes = true;
}

