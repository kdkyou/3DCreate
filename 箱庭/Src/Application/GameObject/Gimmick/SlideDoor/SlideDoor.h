#pragma once

#include"../GimmickBase/GimmickBase.h"

#define RIMIT_HEIGHT 6.0

class SlideDoor :public GimmickBase
{
public:
	SlideDoor(){}
	~SlideDoor(){}

	void Init()override;
	void Update()override;
	

	void DrawUnLit()override;
	void DrawBright()override;

	void OnHit()override;
	void OnEncount()override;

private:
	
	//初期座標
	Math::Vector3	m_iniPos = {};
	
	//行列
	Math::Matrix	m_mRot;

	float			m_speed = 0.0f;
	float			m_ang = 0;

	
};