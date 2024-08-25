#include "DiceManager.h"

#include"../Character/Character.h"

void DiceManager::Init()
{
	m_skillTex=std::make_shared<KdTexture>();
	m_skillTex->Load("Asset/Textures/GameObject/Dice/skill.png");
}

void DiceManager::Update()
{
	if (!m_spChara)return;

	m_spChara->Dice();
}

void DiceManager::DrawSprite()
{
	if (!m_skillTex)return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_skillTex,m_skillPos.x,m_skillPos.y);
}
