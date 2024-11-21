#pragma once
#include"../BaseGimmick/BaseGimmick.h"

class FallPillar :public GimmickBase
{
public:
	FallPillar(){}
	~FallPillar()override{}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;
	void Init()override;

	void Update()override;
	void PostUpdate()override;

	void OnHit()override;

private:

	//当たり判定するかどうか
	bool   m_judgeFlg = false;

};
