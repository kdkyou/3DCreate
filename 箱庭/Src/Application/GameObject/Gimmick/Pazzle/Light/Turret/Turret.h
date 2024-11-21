#pragma once
#include"../LaserObject.h"

class Turret :public LaserObject
{
public:
	Turret(){}
	~Turret(){}

	void Init()override;

	void Update()override;
	void PostUpdate()override;

	void OnBright()override;

private:

};