#pragma once

#include"../BaseScene/BaseScene.h"

constexpr int RELIEFCOUNT = 11;

class GimmickScene:public BaseScene
{
public:
	GimmickScene() { }
	~GimmickScene(){}

private:

	void Init()override;
	void Event()override;

	
};