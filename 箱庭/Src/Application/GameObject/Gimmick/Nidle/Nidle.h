#pragma once

#include"../BaseGimmick/BaseGimmick.h"



class Nidle :public BaseGimmick
{
public:
	Nidle(){}
	~Nidle()override{}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;

	void Update()override;
	void PostUpdate()override;

	void OnHit()override;
	void OnEncount()override;
	
private:



};
