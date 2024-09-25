#pragma once
#include"../BaseGimmick/BaseGimmick.h"

class Wall :public BaseGimmick
{
public:

	enum InOut
	{
		None,
		In,
		Out,
	};

	Wall() {}
	~Wall()override {}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;

	void Init()override;
	void PostUpdate()override;

	void OnEncount()override;
	
private:

	InOut	m_type;

};