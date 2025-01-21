#pragma once
#include"../GimmickBase/GimmickBase.h"


class PitFall :public GimmickBase
{
public:

	enum OpenClose
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

protected:


	OpenClose	m_type = OpenClose::None;

	int		m_coolTime = 0;
	bool	m_coolFlg = false;


};