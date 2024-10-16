#include "Terrain.h"


void Terrain::Update()
{
	m_drawFlg = false;
}

void Terrain::GenerateDepthMapFromLight()
{
	if (!m_spModel) return;
//	if (!m_drawFlg)return;
	//static Math::Vector2 offset = { 0,0 };
	//offset.x += WATER_SPEED;
	//offset.y += WATER_SPEED;
	//if (offset.x > 1)
	//{
	//	offset.x -= 1;
	//}
	//if (offset.y > 1)
	//{
	//	offset.x -= 1;
	//}
	//KdShaderManager::Instance().m_StandardShader.SetWaterUVOffset(offset);

	////テクスチャの数を増やす
	//KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 2,2 });

	//KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
	//KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

}

void Terrain::DrawLit()
{
	if (!m_spModel) return;
//	if (!m_drawFlg)return;
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
//		KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 2,2 });

		KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
		KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);
}

void Terrain::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);

	////水面表現２　テクスチャを読み込む
	//m_spnormalTex = std::make_shared<KdTexture>();
	//m_spnormalTex->Load("Asset/Textures/GameObject/Shader/water3.png");

	////水面表現6 GPUにテクスチャを転送
	//KdShaderManager::Instance().m_StandardShader.SetWaterNormalTexture(*m_spnormalTex);
}

void Terrain::OnHit()
{
	//m_drawFlg = true;
}

void Terrain::Release()
{
	m_spModel = nullptr;
}

