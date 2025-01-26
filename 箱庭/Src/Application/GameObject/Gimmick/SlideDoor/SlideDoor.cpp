#include "SlideDoor.h"

#include"../../Dice/DiceManager.h"

#include"../../../AssetRepository/AssetRepository.h"
#include"../../../Scene/SceneManager.h"

void SlideDoor::Init()
{
	m_isOnes = false;

	m_speed = 0.05f;
	
	m_iniPos = GetPos();

	m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
	
	m_spModel = AssetRepository::Instance().GetModel("BreakWall");
	
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("slide",m_spModel, KdCollider::TypeGround|KdCollider::TypeEvent);
	

//	DiceManager::GetInstance().Init();

}

void SlideDoor::Update()
{
	if (!m_isOnes)return;

		m_ang += 30.0f;
		if (m_ang > 360.0f)
		{
			m_ang -= 360.0f;
		}

		{
			if (m_pos.y < m_iniPos.y + RIMIT_HEIGHT)
			{
				m_pos.z = m_iniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
				m_pos.y += m_speed;
				m_mWorld = m_mRot * Math::Matrix::CreateTranslation(m_pos);
			}
			else
			{
				m_pCollider->SetEnable("Door", false);
			}
		}

	Math::Vector3 vec = (Math::Matrix::CreateTranslation(Math::Vector3{ -3,0,0 }) * m_mWorld).Translation();

	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 3,3,3 }, 5.0f, vec);


	DiceManager::GetInstance().Update();
}

void SlideDoor::DrawUnLit()
{
	DiceManager::GetInstance().DrawUnLit();
}

void SlideDoor::DrawBright()
{
	DiceManager::GetInstance().DrawBright();
}

void SlideDoor::OnHit()
{
	if (DiceManager::GetInstance().ReadKey())
	{
		m_isOnes = true;
	}
}

void SlideDoor::OnEncount()
{
	
}






