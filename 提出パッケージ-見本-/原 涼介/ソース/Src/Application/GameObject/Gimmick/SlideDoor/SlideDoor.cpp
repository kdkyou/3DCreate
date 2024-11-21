#include "SlideDoor.h"

#include"../../Dice/DiceManager.h"

#include"../../../AssetRepository/AssetRepository.h"
#include"../../../Scene/SceneManager.h"

void SlideDoor::Init()
{
	m_lrFlg = LR::None;
	m_isOnes = false;
	
	m_rightIniPos = { 0.0f,0.0f,8.0f };
	m_leftIniPos = { 0.0f,0.0f,-8.0f };

	m_speed = 0.05f;
	
	m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mRight = m_mRot * Math::Matrix::CreateTranslation(m_rightIniPos) ;
	m_mLeft = m_mRot * Math::Matrix::CreateTranslation(m_leftIniPos);
	
	m_spModel = AssetRepository::Instance().GetModel("BreakWall");
	m_spModelLeft = AssetRepository::Instance().GetModel("BreakWall");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("slide",{},2.0f, KdCollider::TypeEvent);

	m_pCollider->RegisterCollisionShape("DoorR", m_spModel,m_mRight, KdCollider::TypeGround);
	m_pCollider->RegisterCollisionShape("DoorL", m_spModelLeft,m_mLeft, KdCollider::TypeGround);
	
	m_mRight =m_mRight * m_mWorld;
	m_mLeft =m_mLeft * m_mWorld;

//	DiceManager::GetInstance().Init();

}

void SlideDoor::Update()
{
	if (m_lrFlg!=LR::None)
	{
		m_ang += 30.0f;
		if (m_ang > 360.0f)
		{
			m_ang -= 360.0f;
		}

		if (m_lrFlg == LR::Right)
		{
			if (m_rightPos.y < m_rightIniPos.y + RIMIT_HEIGHT)
			{
				m_rightPos.z = m_rightIniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
				m_rightPos.y += m_speed;
				m_mRight = m_mRot * Math::Matrix::CreateTranslation(m_rightPos) * m_mWorld;
				KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 5,5,5 }, 5.0f, m_mRight.Translation());
			}
			else
			{
				m_lrFlg = LR::None;
				m_pCollider->SetEnable("DoorR", false);
			}
		}
		if (m_lrFlg == LR::Left)
		{
			if (m_leftPos.y < m_leftIniPos.y + RIMIT_HEIGHT)
			{
				m_leftPos.z = m_leftIniPos.z + sin(DirectX::XMConvertToRadians(m_ang)) * 0.1f;
				m_leftPos.y += m_speed;
				m_mLeft = m_mRot * Math::Matrix::CreateTranslation(m_leftPos) * m_mWorld;
				KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 5,5,5 }, 5.0f, m_mLeft.Translation());
			}
			else
			{
				m_lrFlg = LR::None;
				m_pCollider->SetEnable("DoorL", false);

			}
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

void SlideDoor::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
	}
	if (m_spModelLeft)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelLeft, m_mLeft);
	}
}

void SlideDoor::DrawLit()
{
	static Math::Vector2 offset = { 0.0f,0.0f };
	offset.x += WATER_SPEED;
	offset.y += WATER_SPEED;
	if (offset.x > 1.0f)
	{
		offset.x -= 1.0f;
	}
	if (offset.y > 1.0f)
	{
		offset.x -= 1.0f;
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterUVOffset(offset);

	//板ポリに張るテクスチャの数を増やす
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 4,4 });

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);

	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);

	static Math::Vector2 twoOffset = { 0.0f,0.0f };
	twoOffset.x += WATER_SPEED;
	twoOffset.y += WATER_SPEED;
	if (twoOffset.x > 1.0f)
	{
		twoOffset.x -= 1.0f;
	}
	if (twoOffset.y > 1.0f)
	{
		twoOffset.x -= 1.0f;
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterUVOffset(twoOffset);

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
	
	if (m_spModelLeft)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelLeft, m_mLeft);
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);
}

void SlideDoor::DrawSprite()
{
	DiceManager::GetInstance().DrawSprite();
}



void SlideDoor::OnEncount()
{
	if (m_isOnes)return;

		DiceManager::GetInstance().Ready(m_mWorld);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		bool flg = DiceManager::GetInstance().Dice(60);
		KdAudioManager::Instance().Play("Asset/Sounds/SE/Wall.wav");
		m_isOnes = true;
		if (flg)
		{
			m_lrFlg = LR::Right;
		}
		else
		{
			m_lrFlg = LR::Left;
		}
	}
}



