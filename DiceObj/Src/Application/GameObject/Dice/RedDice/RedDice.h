#pragma once

#define HALF 0.5

#include"../DiceBase.h"

class RedDice :public DiceBase
{
public:
	RedDice(){}
	~RedDice()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	
	void Shake(const int _number)override;

private:



};
