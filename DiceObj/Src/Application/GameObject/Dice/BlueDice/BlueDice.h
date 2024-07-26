#pragma once

#include"../DiceBase.h"

class BlueDice :public DiceBase
{
public:
	BlueDice() {}
	~BlueDice()override { Release();}

	void Init()override;
	void Update()override;


	void Shake(const int _number)override;

private:

	void Release();

};
