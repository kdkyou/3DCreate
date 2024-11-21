#pragma once
#include"../LaserObject.h"

class Laser :public LaserObject
{
public:

	void Init()override;

	void Update()override;
	void PostUpdate()override;

	void OnHit()override;

private:
};