#pragma once

#include"../BaseScene/BaseScene.h"

class MapScene :public BaseScene
{
public:
	MapScene() { Init();}
	~MapScene()override{}

private:

	void Init()override;
	
};

