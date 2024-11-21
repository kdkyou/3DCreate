#pragma once
#include"../BaseGimmick/BaseGimmick.h"

#define RIMIT_HEIGHT 


class Door :public BaseGimmick
{
public:
	Door(){}
	~Door()override{}

	void Update()override;

	void SetParam(const Math::Matrix& mat);
	void SetModel(const std::shared_ptr<KdModelData>& model)override;

	void Start();

private:

	//初期座標
	Math::Vector3	m_iniPos = {};

	float m_speed =0.0f;
	int m_ang = 0;


};