#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public :

	GameScene()		{ Init(); }
	~GameScene()	{}

private:

	void Event() override;
	void Init() override;

	// 乱数生成器
	std::shared_ptr<KdRandomGenerator> m_RandomGen;

	std::shared_ptr<KdModelWork> m_spRDiceModel = nullptr;
	std::shared_ptr<KdModelData> m_spBDiceModel = nullptr;

};
