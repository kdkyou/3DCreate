#pragma once

#include"../CameraBase.h"

class FreeCamera :public CameraBase
{
public:
	FreeCamera(){}
	~FreeCamera()override{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

private:

	Math::Vector3 m_pos;

};