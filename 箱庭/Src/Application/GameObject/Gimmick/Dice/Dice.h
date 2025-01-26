#pragma once

#include"../GimmickBase/GimmickBase.h"

class Dice :public GimmickBase
{
public:

	Dice(){}
	~Dice()override{}

	void SetMaterial(std::string _fileName,bool BorR);

	void Update()override;

	void GenerateDepthMapFromLight()override{}
	void DrawLit()override {}
	void DrawUnLit()override;

	void OnHit()override;

private:

	//true...青,false...赤
	bool m_BorR=false;
	bool m_dissolveFlg=false;
	float m_dissolve = 0.0f;

};