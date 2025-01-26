#pragma once

#include"../WeaponBase.h"

class Light:public WeaponBase
{
public:
	Light(){}
	~Light()override{}

	void Update()override;
	
	void Init()override;
	
private:

	float m_rotAng  = 0.0f;

	
};
