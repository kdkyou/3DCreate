﻿#pragma once

#define COOL_TIME 120

#define ONE_AROUND 360

class GimmickBase :public KdGameObject
{
public:
	GimmickBase() {}
	~GimmickBase()override {}

	virtual void SetModel(const std::shared_ptr<KdModelData>& model) { m_spModel = model; }
	virtual void SetModel(const std::shared_ptr<KdModelWork>& model) { m_spWkModel = model; }

	virtual void GenerateDepthMapFromLight()override;
	virtual void DrawLit()override;
	
	void OnBright()override;

protected:

	std::shared_ptr<KdModelData>	m_spModel = nullptr;
	std::shared_ptr<KdModelWork>	m_spWkModel = nullptr;

	std::shared_ptr<KdAnimator>		m_spAnimator = nullptr;

	Math::Vector3					m_pos;

	int								m_coolTime = 0;

	//一度切りのギミック
	bool							m_isOnes = false;

};
