#pragma once

#include"../BaseScene/BaseScene.h"

class NoiseScene:public BaseScene
{
public:
	NoiseScene() { Init(); }
	~NoiseScene()override;

private:
	void Init()override;

};
