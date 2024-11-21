#include "RotateBridge.h"

void RotateBridge::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RotBridge", m_spModel, KdCollider::TypeGround);

	const static KdModelData::Node* _p1Node = m_spModel->FindNode("GearP");
	if (_p1Node)
	{
		m_mGear = m_mWorld * _p1Node->m_worldTransform;
	}
}

void RotateBridge::SetModel(const std::shared_ptr<KdModelWork>& model)
{
	m_spWkModel = model;
	
	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spWkModel->GetAnimation("Rotate"));
}

void RotateBridge::Init()
{
	m_ang = 0;
	m_spin = 0;
	m_stopFrame = STOP_FRAME;
}

void RotateBridge::Update()
{
	//停止時間のクールタイム
	m_stopFrame--;
	if (m_stopFrame <= 0)
	{
		m_rotFlg = true;
		m_stopFrame = 0;
		m_isOnes = false;
	}

	//回転
	if (m_rotFlg)
	{
		

		if (m_spin < ROTATE_ONCE_RIMIT)
		{
			//回転計測
			m_spin++;
			m_ang+=ADD_ANGLE;
			m_num = ADD_ANGLE;
//			KdAudioManager::Instance().Play3D("Asset/Sounds/SE/AroundN.wav", m_pos);
		}
		else
		{
			m_spin = 0;
			m_num = 0;
			m_stopFrame = STOP_FRAME;
			m_rotFlg = false;
			if (!m_isOnes)
			{
				m_isOnes = true;
//				KdAudioManager::Instance().Play3D("Asset/Sounds/SE/AroundE.wav", m_pos);
			}
		}
	}

	if (m_ang>360)
	{
		m_ang -= 360;
	}

	
	
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_ang));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	m_mWorld = rotMat * transMat;
}


void RotateBridge::PostUpdate()
{
	m_spAnimator->AdvanceTime(m_spWkModel->WorkNodes());
}

void RotateBridge::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mGear);
	}
}

void RotateBridge::DrawLit()
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

	//モデルに張るテクスチャの数を増やす
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 4,4 });

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);


	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mGear);
	}

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);
}


