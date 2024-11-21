#pragma once
#include"../GimmickBase/GimmickBase.h"

class BreakWall :public GimmickBase
{
public:
	BreakWall(){}
	~BreakWall()override{}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;

	void Init()override;
	void PostUpdate()override;

	void OnHit()override;

private:

};
