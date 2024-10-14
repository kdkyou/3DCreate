#include "Noise.h"

#include"../../Scene/SceneManager.h"

void Noise::Init()
{
	m_tex = std::make_shared<KdTexture>();

}

void Noise::Update()
{

}

void Noise::PostUpdate()
{
}

void Noise::DrawUnLit()
{

}

void Noise::DrawSprite()
{
	if (!m_tex) return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0);
}

void Noise::SetTexture(const std::shared_ptr<KdTexture>& _tex)
{
}
