#pragma once

#define BRIGHT_TIME 120

class BaseGimmick :public KdGameObject
{
public:
	BaseGimmick(){}
	~BaseGimmick()override{}

	virtual void SetModel(const std::shared_ptr<KdModelData>& model){}
	virtual void SetModel(const std::shared_ptr<KdModelWork>& model){}

	virtual void GenerateDepthMapFromLight()override;
	virtual void DrawLit()override;
	//void DrawBright()override;

	void OnBright()override;

protected:
	
	std::shared_ptr<KdModelData>	m_spModel = nullptr;
	std::shared_ptr<KdModelWork>	m_spWkModel = nullptr;

	std::shared_ptr<KdAnimator>		m_spAnimator = nullptr;

	Math::Vector3					m_pos;

	int								m_brightTime=0;

	//一度切りのギミック
	bool							m_isOnes = false;

};
