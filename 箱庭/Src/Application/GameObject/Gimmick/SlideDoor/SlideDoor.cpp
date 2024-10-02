#include "SlideDoor.h"

#include"../../Dice/DiceManager.h"

void SlideDoor::Init()
{
	m_lrFlg = LR::None;
}

void SlideDoor::Update()
{
	if (m_lrFlg == LR::Right)
	{
		m_right.y += 0.01f;
	}
}

void SlideDoor::PostUpdate()
{
}

void SlideDoor::DrawUnLit()
{
	DiceManager::GetInstance().DrawUnLit();
}

void SlideDoor::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mLeft);
	}
}

void SlideDoor::GenerateDepthMapFromLight()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mRight);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mLeft);
	}
}


void SlideDoor::OnEncount()
{

}
