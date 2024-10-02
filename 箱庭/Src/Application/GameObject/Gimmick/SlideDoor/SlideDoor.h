#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class SlideDoor :public BaseGimmick
{
public:
	SlideDoor(){}
	~SlideDoor(){}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void DrawUnLit()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void OnEncount()override;

private:

	enum LR
	{
		None,
		Left,
		Right,
	};

	//行列
	Math::Matrix m_mRight;
	Math::Matrix m_mLeft;

	//座標
	Math::Vector3 m_right;
	Math::Vector3 m_left;


	//
	LR	m_lrFlg =LR::None;
};