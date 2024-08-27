#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class Nidle :public BaseGimmick
{
public:
	Nidle(){}
	~Nidle()override{}

	void SetModel(std::shared_ptr<KdModelWork>& model)override;

	void Update()override;
	void PostUpdate()override;

	void OnHit()override;
	void OnEncount()override;
	
private:

	std::shared_ptr<KdAnimator>			m_spAnimetor = nullptr;


};
