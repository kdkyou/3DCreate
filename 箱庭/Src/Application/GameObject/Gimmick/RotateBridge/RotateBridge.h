#pragma once
#include"../BaseGimmick/BaseGimmick.h"

class RotateBridge :public BaseGimmick
{
public:
	RotateBridge() {}
	~RotateBridge()override {}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;
	
	/*void Init()override;
	void Update()override;
	*/
	void PostUpdate()override;

	//void OnHit()override;

	bool IsRideable()const { return true; }

private:


};
