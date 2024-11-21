#include "DiceManager.h"

#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"
#include"../Camera/CameraBase.h"

void DiceManager::Update()
{
	m_drawTime--;
	if (m_drawTime < 0)
	{
		m_drawTime = 0;
		m_spBlueD = nullptr;
		m_spRedD = nullptr;
	}
}

void DiceManager::DrawUnLit()
{
	if (m_spBlueD)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD,m_mBlueD);
	}
	if (m_spRedD)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD,m_mRedD);
	}

}

const bool DiceManager::Dice(const int _judgeNum)
{
	int l_num = m_randGen.GetInt(1, 100);

	bool ONOFF = false;

	std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();

	std::shared_ptr<Cutin> _cut = std::make_shared<Cutin>();


	if (l_num <= _judgeNum)
	{
		if (l_num <= CRITICAL_RANGE)
		{
			_cut->Set(TEXTUREPASS "Critical.png", SOUNDPASS"Critical.wav");
		}
		else
		{
			_cut->Set(TEXTUREPASS "", SOUNDPASS"Success.wav");
		}
		ONOFF = true;
	}
	else
	{
		if (l_num >= FUMBLE_RANGE)
		{
			_cut->Set(TEXTUREPASS "Fumble.png", SOUNDPASS"Fumble.wav");
		}
		else
		{
			_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
		}
	}
	SceneManager::Instance().AddObject(_cut);

	std::shared_ptr<BlueDice> _blueDice = std::make_shared<BlueDice>();
	_blueDice->SetModel(AssetRepository::Instance().GetModel("BlueDice"));
	_blueDice->Init();
	_blueDice->SetCamera(_spCamera);

	std::shared_ptr<RedDice> _redDice = std::make_shared<RedDice>();
	_redDice->SetModel(AssetRepository::Instance().GetModel("RedDice"));
	_redDice->Init();
	_redDice->SetCamera(_spCamera);

	int l_tens = l_num / TEN;
	_redDice->Shake(l_tens, { 0.8f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });
	int l_ones = l_num % TEN;
	_blueDice->Shake(l_ones, { 1.f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });

	SceneManager::Instance().AddObject(_redDice);
	SceneManager::Instance().AddObject(_blueDice);

	return ONOFF;
}

void DiceManager::Ready(const Math::Matrix& _mat)
{
	m_spBlueD = AssetRepository::Instance().GetModel("BlueDice");
	m_spRedD = AssetRepository::Instance().GetModel("RedDice");
	m_drawTime = DRAW_TIME;
	m_mBlueD = Math::Matrix::CreateScale(0.4f) * Math::Matrix::CreateTranslation({ -2.f,1.5f,2.f }) * _mat;
	m_mRedD = Math::Matrix::CreateScale(0.4f) * Math::Matrix::CreateTranslation({ -2.f,1.5f,-0.f }) * _mat;
}

void DiceManager::DrawSprite()
{
	if (m_drawTime <= 0)return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0);
}

void DiceManager::Init()
{
	if (!m_tex)
	{
		m_tex = std::make_shared<KdTexture>();
		m_tex->Load("Asset/Textures/GameObject/Relief/F.png");
	}
}


void DiceManager::Release()
{
	m_spBlueD = nullptr;
	m_spRedD = nullptr;
}

