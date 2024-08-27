#include "Information.h"

void Information::SetTexture(const std::string& path,bool longOrshort)
{
	if (!m_tex)
	{
		m_tex = std::make_shared<KdTexture>();
		m_tex->Load(path);
	}
	if (longOrshort)
	{
		m_showTime = SHOW_TIME;
	}
	else
	{
		m_showTime = SHOW_SHORT;
	}
}

void Information::Update()
{
	m_showTime--;

	if (m_showTime < 0)
	{
		m_isExpired = true;
	}
}

void Information::DrawSprite()
{
	if (!m_tex)return;

	Math::Color _color = { 1,1,1,0.6f };

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0,nullptr,&_color);
}
