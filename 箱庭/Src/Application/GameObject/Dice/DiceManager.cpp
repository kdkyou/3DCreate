#include "DiceManager.h"

#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

void DiceManager::Update()
{
	
}

void DiceManager::DrawUnLit()
{
	if (m_spBlueD)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD);
	}
	if (m_spRedD)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD);
	}

}

const bool DiceManager::Dice(const int _judgeNum,const std::weak_ptr<CameraBase>& _wpCamera)
{
	int l_num = m_randGen.GetInt(1, 100);

	std::shared_ptr<CameraBase> _spCamera = _wpCamera.lock();

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

	return false;
}

void DiceManager::Release()
{

	m_spBlueD = nullptr;
	m_spRedD = nullptr;
}

