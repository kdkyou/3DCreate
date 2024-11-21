#pragma once

#include"../BaseScene/BaseScene.h"
#define TWO_SECOND 120 

class Fade;

class ResultScene : public BaseScene
{
public:
	ResultScene() { Init(); }
	~ResultScene() {}

private:

	void Init()override;
	void Event()override;

	int m_frame = 0;
	std::weak_ptr<Fade>			m_wpFade;

};