#pragma once

#include"../BaseGimmick/BaseGimmick.h"

#define RIMIT_HEIGHT 6.0

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

	void SetModel(const std::shared_ptr<KdModelData>& model)override;

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

	float m_speed;
	int m_ang;

	//
	LR	m_lrFlg =LR::None;
};