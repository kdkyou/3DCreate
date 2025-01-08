#pragma once

#include"../GimmickBase/GimmickBase.h"

//定数の定義
constexpr float EPSILON = 0.01f;	//角度の許容誤差

//ギミックベースを継承したレーザーギミックに使う元のクラス
class PuzzleObject :public GimmickBase
{
public:
	PuzzleObject(){}
	~PuzzleObject(){}

	
	//現在の角度を取得
	const float GetAngle()const { return m_angle; }
	//初期の角度と目標角度を設定
	void SetAngles(float _angle,float _targetAngle) { 
		m_angle = _angle; 
		m_targetAngle = _targetAngle;
	}

	// 目標角度に一致しているか確認
	bool IsAligned() const {
		return std::abs(m_angle - m_targetAngle) < EPSILON;
	}

protected:

	float m_angle = 0;
	float m_targetAngle = 0;

};