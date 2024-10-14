#include "Noise.h"

#include"../../Scene/SceneManager.h"

void Noise::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_noisePoly = std::make_shared<KdSquarePolygon>();

	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 5, 0);

	Math::Matrix scaleMat = Math::Matrix::CreateScale(10, 10, 1);

	m_mWorld = scaleMat * transMat;
}

void Noise::Update()
{
	m_tex = SceneManager::Instance().GetRenderTargetTexture();
	m_drawLength = SceneManager::Instance().GetLength();
	SceneManager::Instance().ChangeRenderTarget();
	for (int i = 0; i < m_tex->GetHeight(); i += m_drawLength)
	{

	}
	SceneManager::Instance().UndoRenderTarget();
}

void Noise::PostUpdate()
{
}

void Noise::DrawUnLit()
{
	if (!m_noisePoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_noisePoly,m_mWorld);
}

void Noise::DrawLit()
{
	if (!m_noisePoly) return;

	//KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_noisePoly, m_mWorld);
}

void Noise::DrawSprite()
{
	/*if (!m_tex) return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0);*/
}

void Noise::SetTexture(const std::shared_ptr<KdTexture>& _tex)
{
}
