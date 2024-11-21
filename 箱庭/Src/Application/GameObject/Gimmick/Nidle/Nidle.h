#pragma once

#include"../GimmickBase/GimmickBase.h"



class Nidle :public GimmickBase
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
