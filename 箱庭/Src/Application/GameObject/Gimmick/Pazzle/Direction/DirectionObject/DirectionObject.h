#pragma once
#include"../../PuzzleObject.h"

class DirectionObject :public PuzzleObject{

public:
	
	DirectionObject(){}
	~DirectionObject()override{}

	void Init()override;
	void Update()override;

	void OnBright()override;

private:

	const int AddCount = 1;

};