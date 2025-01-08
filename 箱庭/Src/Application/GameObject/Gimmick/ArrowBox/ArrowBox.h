#pragma once
#include"../GimmickBase/GImmickBase.h"

#define COOL_TIME 120

class ArrowBox :public GimmickBase
{
public:
	ArrowBox(){}
	~ArrowBox()override{}

	 enum Pattern 
	{
		 None,
		 One,
		 Two,
		 Three,
		 Four,
		 Five,
	};

	void Init()override;
	void SetModel(const std::shared_ptr<KdModelData>& model)override;

	void Update()override;

	void OnEncount()override;

private:

	const int Count = 1;
	
	Pattern m_nowPattern = Pattern::None;

	KdRandomGenerator m_random;

};