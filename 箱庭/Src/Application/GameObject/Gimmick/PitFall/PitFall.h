#pragma once
#include"../BaseGimmick/BaseGimmick.h"

#define RECAST_TIME  180 

class PitFall :public BaseGimmick
{
public:

	enum InOut
	{
		None,
		Open,
		Close,
	};

	PitFall() {}
	~PitFall()override {}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void OnEncount()override;

private:

	InOut	m_type = InOut::None;

	int		m_coolTime = 0;
	bool	m_coolFlg = false;

};