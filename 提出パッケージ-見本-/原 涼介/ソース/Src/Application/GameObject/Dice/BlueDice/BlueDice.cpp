﻿#include "BlueDice.h"

#include"../../../main.h"

void BlueDice::Init()
{
	m_pos = {0,-0.0f,1.0f};
	m_moveDir = {};
	m_rotDir = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mScaleMat = Math::Matrix::CreateScale(RFONE);
	m_mRotMat = Math::Matrix::CreateFromYawPitchRoll(m_rot);
	m_mWorld = m_mScaleMat * m_mRotMat * _transMat;

}


void BlueDice::Shake(const int _number, const Math::Vector3& _pos, const Math::Vector3& _moveDir, const float _speed, const Math::Vector3& _rotDir)
{
	switch (_number)
	{
	case 0:
		m_DecidedRot = { 3.7f,3.4f,0.0f };
		break;
	case 1:
		m_DecidedRot = { 357.f,1.7f,0.f };
		break;
	case 2:
		m_DecidedRot = { 3.f,0.f,0.f };
		break;
	case 3:
		m_DecidedRot = { 1.f,4.1f,0.f };
		break;
	case 4:
		m_DecidedRot = { 1.f,5.3f,1.f };
		break;
	case 5:
		m_DecidedRot = { 2.2f,1.3f,0.f };
		break;
	case 6:
		m_DecidedRot = { 1.f,2.9f,0.f };
		break;
	case 7:
		m_DecidedRot = { 3.8f,2.4f,0.f };
		break;
	case 8:
		m_DecidedRot = { 357.6f,0.5f,0.f };
		break;
	case 9:
		m_DecidedRot = { 3.7f,4.7f,0. };
		break;
	default:
		break;
	}
	m_pos = _pos;
	m_moveDir = _moveDir;
	m_moveDir.Normalize();
	m_moveSpeed = _speed;
	m_rotDir = _rotDir;
	m_showFrame = 60;

	
}

void BlueDice::Release()
{
}
