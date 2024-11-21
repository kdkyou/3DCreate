#pragma once
#include"../GimmickBase/GimmickBase.h"

class Close:public GimmickBase
{
public:
	Close(){}
	~Close()override{}

	void SetModel(const std::shared_ptr<KdModelData>& model)override;

	void Update()override;


private:

};
