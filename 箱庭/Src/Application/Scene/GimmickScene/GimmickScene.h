#pragma once

#include"../BaseScene/BaseScene.h"

#define RELIEFCOUNT 11

class GimmickScene:public BaseScene
{
public:
	GimmickScene() { Init(); }
	~GimmickScene(){}

private:

	void Init()override;
	void Event()override;

	int time;
};