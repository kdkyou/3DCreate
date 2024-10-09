#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class Door;

class SlideDoor :public BaseGimmick
{
public:
	SlideDoor(){}
	~SlideDoor(){}

	void Init()override;
	void Update()override;
	
	void DrawUnLit()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void OnEncount()override;


private:

	enum LR
	{
		None,
		Left,
		Right,
	};

	//モデル情報
	std::shared_ptr<KdModelData> m_spModelLeft = nullptr;

	//座標
	Math::Vector3	m_rightPos = {};
	Math::Vector3	m_leftPos = {};

	//初期座標
	Math::Vector3	m_rightIniPos = {};
	Math::Vector3	m_leftIniPos = {};

	//行列
	Math::Matrix	m_mRight;
	Math::Matrix	m_mLeft;
	Math::Matrix	m_mRot;

	float			m_speed = 0.0f;
	float			m_ang = 0;

	//std::weak_ptr<Door>	m_right;
	//std::weak_ptr<Door>	m_left;

	
	//
	LR	m_lrFlg =LR::None;
};