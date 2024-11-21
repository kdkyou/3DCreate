#pragma once

#include"../DiceBase/DiceBase.h"

class RedDice :public DiceBase
{
public:
	RedDice(){}
	~RedDice()override{}

	void Init()override;
	
	void Shake(const int _number, const Math::Vector3& _pos, const Math::Vector3& _moveDir, const float _speed, const Math::Vector3& _rotDir)override;

private:



};
