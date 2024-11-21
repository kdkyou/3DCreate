#include "Noise.h"

#include"../../Scene/SceneManager.h"

//void Noise::Init()
//{
//	m_renderTex = std::make_shared<KdTexture>();
//	m_apotheosisTex = std::make_shared<KdTexture>();
//	m_totalTex = std::make_shared<KdTexture>();
//
//	m_noisePoly= std::make_shared<KdSquarePolygon>();
//	//座標
//	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 5, 0);
//
//	Math::Matrix scaleMat = Math::Matrix::CreateScale(10, 10, 1);
//
//	m_mWorld = scaleMat * transMat;
//
//}

void Noise::Update()
{
	m_ang++;
	if (m_ang > 360) {
		m_ang -= 360;
	}

	m_aliveTime--;
	if (m_aliveTime < 0)
	{
		m_aliveTime = 0;
		m_isExpired = true;
		if (m_isPlayMusic)
		{
			KdAudioManager::Instance().StopAllSound();
			KdAudioManager::Instance().Play("Asset/Sounds/BGM/R'lyeh.wav", true);
			KdAudioManager::Instance().Play("Asset/Sounds/BGM/babul.wav", true);
		}
	}

//	m_noisePoly->SetMaterial(SceneManager::Instance().GetRenderTargetTexture());
}

void Noise::PreDraw()
{
	/*m_renderTex = SceneManager::Instance().GetRenderTargetTexture();
	SceneManager::Instance().ChangeRenderTarget();
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_renderTex, 0, 0);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_apotheosisTex, 0, 0);
	SceneManager::Instance().UndoRenderTarget();
	m_totalTex = SceneManager::Instance().GetRenderTargetTexture();*/

	int height = m_apotheosisTex->GetHeight();
	for (int i = 0; i < height; i += m_drawLength)
	{
		m_pos.x = CENTER + gene.GetInt(1, m_waveLength) - m_waveLength / 2;
		m_pos.y = (height / 2.0f) - i;
		long width = m_apotheosisTex->GetWidth();
		Math::Rectangle rect = { 0,0 + i,width,m_drawLength };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_apotheosisTex, m_pos.x, m_pos.y, width, m_drawLength, &rect,&m_color);
	}

}

void Noise::DrawUnLit()
{
	if (!m_noisePoly)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_noisePoly,m_mWorld);
}

void Noise::DrawLit()
{
	if (!m_noisePoly)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_noisePoly, m_mWorld);
}

void Noise::DrawSprite()
{
	if (!m_totalTex)return;
	m_totalTex = SceneManager::Instance().GetRenderTargetTexture();
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_totalTex, 0, 0);
}

void Noise::SetParam(const std::shared_ptr<KdTexture>& _tex,int _aliveTime, int _waveLength, const Math::Color& _colr, bool _isPlay)
{
	m_renderTex = std::make_shared<KdTexture>();
	m_apotheosisTex = std::make_shared<KdTexture>();
	m_totalTex = std::make_shared<KdTexture>();


	m_apotheosisTex = _tex;
	m_aliveTime = _aliveTime;
	m_waveLength = _waveLength;
	m_color = _colr;
	m_isPlayMusic = _isPlay;

	if (m_isPlayMusic)
	{
		KdAudioManager::Instance().Play("Asset/Sounds/BGM/Carol.wav");
	}

	m_drawLength = 1;
}


