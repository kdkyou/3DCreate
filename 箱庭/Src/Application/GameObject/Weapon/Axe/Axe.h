#pragma once

#include"../WeaponBase.h"

class Axe:public WeaponBase
{
public:
	Axe(){}
	~Axe()override{}

	void Update()override;
	void PostUpdate()override;

	void Init()override;
	
private:

	float m_scaleSize;

};
