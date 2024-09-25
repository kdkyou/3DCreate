#pragma once
#include"../BaseGimmick/BaseGimmick.h"

class BreakWall :public BaseGimmick
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
