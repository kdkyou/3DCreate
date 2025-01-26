#include "DiceManager.h"

#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"
#include"../Camera/CameraBase.h"

void DiceManager::Update()
{
	
}

void DiceManager::DrawUnLit()
{
	if (m_keyType ^ Bit::Blue)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD, m_mBlueD);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD, m_mBlue);
	}
	if (m_keyType ^ Bit::Red)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD, m_mRedD);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD, m_mRed);
	}

}

void DiceManager::DrawBright()
{
	if (m_keyType & Bit::Blue)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD, m_mBlueD);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spBlueD, m_mBlue);
	}
	if (m_keyType & Bit::Red)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD, m_mRedD);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spRedD, m_mRed);
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

const bool DiceManager::ReadKey() const
{
	if (m_keyType == (Bit::Blue + Bit::Red))
	{
	return true;
	}
	return false;
}

void DiceManager::Ready(const Math::Matrix& _mat)
{
}


void DiceManager::Init()
{
	m_spBlueD = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Dice/BlueDice/blueDice.gltf");
	m_spRedD = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Dice/RedDice/redDice.gltf");

	m_mBlueD = Math::Matrix::CreateTranslation({ 6.0f,5.0f,-25.0f });
	m_mBlue = Math::Matrix::CreateTranslation({ 25.0f,7.5f,0.0f });
	m_mRedD = Math::Matrix::CreateTranslation({ -6.0f,5.0f,-25.0f });
	m_mRed = Math::Matrix::CreateTranslation({-25.0f,7.5f,0.0f});


}


void DiceManager::Release()
{
	m_spBlueD = nullptr;
	m_spRedD = nullptr;
}

