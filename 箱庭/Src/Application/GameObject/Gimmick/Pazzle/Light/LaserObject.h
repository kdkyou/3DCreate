#pragma once

#include"../../GimmickBase/GimmickBase.h"

//定数の定義
constexpr float EPSILON = 0.01f;	//角度の許容誤差

//ギミックベースを継承したレーザーギミックに使う元のクラス
class LaserObject :public GimmickBase
{
public:
	LaserObject(){}
	~LaserObject(){}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawUnLit()override;

	//現在の角度を取得
	float GetAngle()const { return m_angle; }
	//現在の角度を設定
	void SetAngle(float _angle) { m_angle = _angle; }
	//目標角度を設定
	void SetTargetAngle(float _targetAngle) { m_targetAngle = _targetAngle; }
	// 目標角度に一致しているか確認
	bool IsAligned() const {
		return std::abs(m_angle - m_targetAngle) < EPSILON;
	}

protected:

	std::shared_ptr<KdTrailPolygon>	m_spTrail = nullptr;

	bool m_isShot = false;

	Math::Matrix m_mNpMat;

	float m_angle = 0.0f;
	float m_targetAngle = 0.0f;

};