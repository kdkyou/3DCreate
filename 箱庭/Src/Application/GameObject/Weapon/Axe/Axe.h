#pragma once

#include"../WeaponBase.h"

#define NONE_AROUND 0
#define HALF_AROUND 180

class Axe:public WeaponBase
{
public:
	Axe(){}
	~Axe()override{}

	void Update()override;
	void PostUpdate()override;

	void Init()override;
	
private:

	float m_scaleSize = 0.0f;

	float m_rotAng  = 0.0f;

	bool m_dirtyFlg = false;

};
