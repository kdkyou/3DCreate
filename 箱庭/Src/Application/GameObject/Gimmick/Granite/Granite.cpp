#include "Granite.h"

void Granite::Init()
{
	m_spModel = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Terrains/Gimmick/Granite/Granite.gltf");
}

void Granite::Update()
{
	m_angle.y += addAng;
	if (m_angle.y > ONE_AROUND)
	{
		m_angle.y -= ONE_AROUND;
	}

	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle.y));
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	m_mWorld = rotY * trans;

	if (m_dissolveFlg)
	{
		m_dissolve += 0.005f;
		if (m_dissolve > 1.0f)
		{
			m_isExpired = true;
		}
	}
}

void Granite::DrawUnLit()
{
	if (m_dissolveFlg)
	{
		Math::Vector3 _colr(0.52f, 0.91f, 0.49f);
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, nullptr, &_colr);
	}

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Granite::DrawBright()
{
	if (m_dissolveFlg)return;
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
