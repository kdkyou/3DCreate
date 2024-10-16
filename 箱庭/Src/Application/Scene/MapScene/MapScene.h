#pragma once

#include"../BaseScene/BaseScene.h"

class MapScene :public BaseScene
{
public:
	MapScene() { Init();}
	~MapScene()override{}

private:

	void Init()override;
	
	std::shared_ptr<KdTexture>  m_spnormalTex = nullptr;

};

