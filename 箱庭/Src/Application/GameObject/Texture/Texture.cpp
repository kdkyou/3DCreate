#include"Texture.h"

void Texture::Init()
{
	m_addAlpha = 0.02f;
	m_alpha = 1.0f;
	m_color = { 1,1,1,1};
}

void Texture::Update()
{
	//if(GetAsyncKeyState())

	if (!m_checkAlpha)return;

	m_alpha += m_addAlpha;
	if (m_alpha > 1 || m_alpha < 0.5)
	{
		m_addAlpha *= -1;
	}

	m_color = { 1,1,1,m_alpha };
}

void Texture::DrawSprite()
{
	if (!m_tex)return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_pos.x, m_pos.y,nullptr,&m_color);
}

void Texture::SetTexAlphaPos(const std::string& path, bool check, Math::Vector2 _pos)
{
	if (!m_tex)
	{
		m_tex = std::make_shared<KdTexture>();
		m_tex->Load(path);
	}
	m_checkAlpha = check;
	m_pos = _pos;
}
