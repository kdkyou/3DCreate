#pragma once

#define BRIGHT_TIME 120

class BaseGimmick :public KdGameObject
{
public:
	BaseGimmick(){}
	~BaseGimmick()override{}

	virtual void SetModel(std::shared_ptr<KdModelData>& model){}
	virtual void SetModel(std::shared_ptr<KdModelWork>& model){}

	void DrawLit()override;
	void DrawBright()override;

	void OnBright()override;

protected:
	
	std::shared_ptr<KdModelData>	m_spModel;
	std::shared_ptr<KdModelWork>	m_spWkModel;

	Math::Vector3					m_pos;

	int								m_brightTime=0;

};
