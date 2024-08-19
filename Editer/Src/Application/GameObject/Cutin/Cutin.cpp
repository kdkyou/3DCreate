#include "Cutin.h"

void Cutin::Set(const std::string& _texPass, const std::string& _soundPass)
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load(_texPass);
	m_time = SIXTY;
	KdAudioManager::Instance().Play(_soundPass);
}

void Cutin::Update()
{
	m_time--;

	if (m_time < 0)
	{
		m_isExpired = true;
	}
}

void Cutin::DrawSprite()
{
	if (m_tex == nullptr) return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0);
}
