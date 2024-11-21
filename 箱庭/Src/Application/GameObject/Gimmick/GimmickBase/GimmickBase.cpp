#include "GimmickBase.h"

void GimmickBase::GenerateDepthMapFromLight()
{

	
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mWorld);
	}

}

void GimmickBase::DrawLit()
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
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 6,6 });

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
	if (m_spWkModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWkModel, m_mWorld);
	}

	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);
}


void GimmickBase::OnBright()
{
	m_coolTime = COOL_TIME;
}
