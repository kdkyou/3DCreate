#pragma once

#include"../BaseScene/BaseScene.h"

class NoiseScene:public BaseScene
{
public:
	NoiseScene() { Init(); }
	~NoiseScene(){}

private:
	void Init()override;

};
