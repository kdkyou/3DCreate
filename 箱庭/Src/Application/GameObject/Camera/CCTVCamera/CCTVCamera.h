#pragma once
#include "../CameraBase.h"

class CCTVCamera : public CameraBase
{
public:
	CCTVCamera()						{}
	~CCTVCamera()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

private:
	void UpdateLookAtRotate(const Math::Vector3& targetPos);

	Math::Vector3			m_pos;

	Math::Matrix			m_rotY;
	Math::Matrix			m_rotZ;

	bool					m_flg=false;

};