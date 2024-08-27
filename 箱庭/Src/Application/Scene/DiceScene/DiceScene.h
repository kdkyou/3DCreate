#pragma once

#include"../BaseScene/BaseScene.h"

class DiceManager;
class Character;

class DiceScene :public BaseScene
{
public:
	DiceScene() { Init(); }
	~DiceScene(){}

	//void SetChara(std::shared_ptr<Character> chara);
private:

	void Init()override;

	std::shared_ptr<DiceManager> m_spDiceManager = nullptr;

};
