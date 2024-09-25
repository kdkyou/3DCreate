#include "DiceManager.h"

//#include"../../..Character/Character.h"
//
//void DiceManager::Init()
//{
//	m_skillTex=std::make_shared<KdTexture>();
//	m_skillTex->Load("Asset/Textures/GameObject/Dice/skill.png");
//	m_frameTex=std::make_shared<KdTexture>();
//	m_frameTex->Load("Asset/Textures/GameObject/Dice/frame.png");
//
//	m_skillPos = { -700,0 };
//	m_skillOpenPos = { -400,0 };
//	m_searchPos = { -490,220 };
//	m_listeingPos = { -490,-50 };
//	m_framePos = m_listeingPos;
//
//	m_onFlg = false;
//}
//
//void DiceManager::Update()
//{
//	if (GetAsyncKeyState('W') & 0x8000)m_framePos = m_searchPos;
//	if (GetAsyncKeyState('S') & 0x8000)m_framePos = m_listeingPos;
//
//	m_spChara->DiceSkill();
//}
//
//void DiceManager::DrawSprite()
//{
//	if (!m_skillTex)return;
//
//	KdShaderManager::Instance().m_spriteShader.DrawTex(m_skillTex,m_skillPos.x,m_skillPos.y);
//
//	if (m_onFlg)
//	{
//		KdShaderManager::Instance().m_spriteShader.DrawTex(m_frameTex, m_framePos.x, m_framePos.y);
//	}
//
//}
//
//void DiceManager::SetCharacter(std::shared_ptr<Character>& _chara)
//{
//	m_spChara = _chara;
//}
