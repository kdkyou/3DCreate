#pragma once

#include"../DiceBase.h"

class BlueDice :public DiceBase
{
public:
	BlueDice() {}
	~BlueDice()override { Release();}

	void Init()override;
	void Update()override;

	void Shake(const int _number, const Math::Vector3 _pos, const Math::Vector3 _moveDir, const float _speed, const Math::Vector3 _rotDir)override;


private:

	void Release();

};
