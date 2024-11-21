#pragma once
#include "../CameraBase.h"

#define MOVE_SPEED 10
#define MOVE_COUNT 20


class TPSCamera : public CameraBase
{
public:
	TPSCamera()							{}
	~TPSCamera()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

private:

	Math::Vector3	m_iniPos;
	Math::Vector3   m_pos;
};