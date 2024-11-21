#include "Fade.h"

void Fade::SetFade(FadeType type, int time,const bool OutorIn)
{
	if (completeFade || type == FadeIn || type == FadeOut)
	{
		completeFade = false;
		fadeFrame = 0;
		fadeTime = time;
		nowFadeType = type;
		if (OutorIn==true)
		{
			m_IncDec = 1;
			m_alpha = 0.0f;
		}
		else
		{
			m_IncDec = -1;
			m_alpha = 1.0f;
		}

		switch (nowFadeType)
		{
		case FadeIn:
		case FadeInLeftRight:
		case FadeInRightLeft:
			fillDisplay = false;
			break;
		}
	}
	isLaunch = true;
}

bool Fade::GetFillDisplay() const
{
	return fillDisplay;
}

bool Fade::GetCompleteFade() const
{
	return completeFade;
}

void Fade::Release()
{
	m_spTex = nullptr;
}

Fade::~Fade()
{
	Release();
}

void Fade::Init()
{
	m_spTex = KdAssets::Instance().m_textures.GetData("Asset/Textures/GameObject/Back/blackBack.png");
	completeFade = true;
	fadeFrame = 0;
	fadeTime = 20;
	fillDisplay = false;
	m_IncDec = 0;
	m_alpha = 0.0f;
	isLaunch = false;

}

void Fade::DrawSprite()
{
	Math::Rectangle _rct = { 0, 0,(long)m_spTex->GetWidth(),(long)m_spTex->GetHeight() };
	Math::Color _color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex, 0, 0, &_rct, &_color);	
}

void Fade::Update()
{
	if (!completeFade)
	{
		fadeFrame++;
		m_alpha += m_IncDec * 1.0f / fadeTime;
		if (fadeFrame >= fadeTime)
		{
			completeFade = true;

			switch (nowFadeType)
			{
			case FadeOut:
			case FadeOutLeftRight:
			case FadeOutRightLeft:
				fillDisplay = true;
				break;
			}

		}
	}
}
