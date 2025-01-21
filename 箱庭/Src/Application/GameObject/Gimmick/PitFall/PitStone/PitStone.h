#pragma once
#include"../PitFall.h"

#define CREATE_CAST 10

class PitStone :public PitFall
{
public:

	PitStone(){}
	~PitStone()override{}

	void SetModel(const std::shared_ptr<KdModelWork>& model)override;

	void Init()override;
	void Update()override;
	void GenerateDepthMapFromLight()override{}
	void DrawLit()override{}
	
private:

	void CreateStone();

	int		m_stoneCool = 0;
	KdRandomGenerator randGene;
};

