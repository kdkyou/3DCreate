#include "BlueDice.h"


void BlueDice::Init()
{
	m_pos = {0,-0.5f,1.0f};
	m_moveDir = {};
	m_rotDir = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mScaleMat = Math::Matrix::CreateScale(RFONE);
	m_mWorld = m_mScaleMat *_transMat;
}

void BlueDice::Update()
{
	
	DiceBase::Update();
}

void BlueDice::Shake(const int _number, const Math::Vector3 _pos, const Math::Vector3 _moveDir, const float _speed, const Math::Vector3 _rotDir)
{
	m_pos = _pos;
	m_moveDir = _moveDir;
	m_moveDir.Normalize();
	m_moveSpeed = _speed;
	m_rotDir = _rotDir;
}

void BlueDice::Release()
{
}
