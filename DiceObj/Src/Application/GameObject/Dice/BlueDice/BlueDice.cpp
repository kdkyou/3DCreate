#include "BlueDice.h"

void BlueDice::Init()
{
	m_pos = {};
	m_moveDir = {};
	m_rotDir = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(0.5f);
	m_mWorld = _scaleMat*_transMat;
}

void BlueDice::Update()
{
}

void BlueDice::Shake(const int _number)
{
}

void BlueDice::Release()
{
}
