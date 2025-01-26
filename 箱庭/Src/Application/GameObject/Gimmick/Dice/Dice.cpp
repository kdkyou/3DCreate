#include "Dice.h"
#include"../../Dice/DiceManager.h"

void Dice::SetMaterial(std::string _fileName, bool BorR)
{
	m_spModel = KdAssets::Instance().m_modeldatas.GetData(_fileName);
	m_BorR = BorR;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Dice", m_spModel, KdCollider::TypeGround+KdCollider::TypeEvent);

	m_dissolve = 0.0f;
	m_dissolveFlg = false;
}

void Dice::Update()
{
	if (m_dissolveFlg)
	{
		m_dissolve += 0.005f;
		if (m_dissolve > 1.0f)
		{
			m_isExpired = true;
			if (m_BorR)
			{
				DiceManager::GetInstance().CheckBlueKey();
			}
			else
			{
				DiceManager::GetInstance().CheckRedKey();
			}
		}
	}
}

void Dice::DrawUnLit()
{
	if (m_dissolveFlg)
	{
		Math::Vector3 _colr(0.52f, 0.75f, 0.91f);
		KdShaderManager::Instance().m_StandardShader.SetDissolve(m_dissolve, nullptr, &_colr);
	}

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Dice::OnHit()
{
	m_dissolveFlg = true;
}
