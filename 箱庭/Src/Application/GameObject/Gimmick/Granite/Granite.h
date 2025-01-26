#pragma once

#include"../GimmickBase/GimmickBase.h"

class Granite :public GimmickBase
{
public:
	Granite(){}
	~Granite()override{}

	void Init()override;
	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;
	void DrawLit()override{}
	void GenerateDepthMapFromLight()override{}

private:

	//回転
	const int addAng = 1;

	//ディゾルブフラグ
	bool									m_dissolveFlg = false;
	float									m_dissolve = 0.0f;

};