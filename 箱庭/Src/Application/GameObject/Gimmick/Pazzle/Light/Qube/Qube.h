#pragma once

#include"../LaserObject.h"

class Qube:public LaserObject
{
public:
	Qube(){}
	~Qube(){}

	void Init()override;
	void Update()override;

	void DrawLit()override;
	
	void OnBright()override;

private:

	//ディゾルブ
	float	m_dissolve = 0.0f;

};