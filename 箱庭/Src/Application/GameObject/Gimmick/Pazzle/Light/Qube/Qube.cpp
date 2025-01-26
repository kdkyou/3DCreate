#include "Qube.h"

#include"../../../../../AssetRepository/AssetRepository.h"

void Qube::Init()
{
	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Weapon/Stone/Stone.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Qube", m_spModel, KdCollider::TypeEvent);

	m_dissolve = 0.0f;
	m_isOnes = false;
}

void Qube::Update()
{
	if (!m_isOnes)return;

	m_dissolve += 0.05f;
	if (m_dissolve > 1.0f)
	{
		m_isExpired = true;
	}
}

void Qube::DrawLit()
{
	if (m_isOnes)
	{
		Math::Vector3 _colr(0.29f, 0.31f, 0.65f);
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, nullptr, &_colr);
	}

	if (m_spModel)
	{
		if (!m_isOnes)
		{
			KdShaderManager::Instance().m_StandardShader.SetLimLightEnable(true);
			Math::Vector3 colr = { 0.61f,0.59f,0.6f };
			KdShaderManager::Instance().m_StandardShader.SetLimlightParam(colr, 0.2f);
		}

		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
		KdShaderManager::Instance().m_StandardShader.SetLimLightEnable(false);
	}

}


void Qube::OnBright()
{
	m_isOnes = true;
}
