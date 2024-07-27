#include "RedDice.h"

void RedDice::Init()
{
	m_pos = { 0.2,-0.5f,1.0f };
	m_moveDir = {};
	m_rotDir = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mScaleMat = Math::Matrix::CreateScale(RFONE);
	m_mWorld = m_mScaleMat * _transMat;

	//初期のアニメーションをセットする
	/*m_spAnimetor = std::make_shared<KdAnimator>();
	if (!m_wpModelWork.expired())
	{
		m_spAnimetor->SetAnimation(m_wpModelWork.lock()->GetAnimation("Drop"));
	}*/
}

void RedDice::Update()
{
	DiceBase::Update();
}

void RedDice::PostUpdate()
{
	DiceBase::PostUpdate();
	//アニメーションの更新
	/*m_spAnimetor->AdvanceTime(m_wpModelWork.lock()->WorkNodes());
	m_wpModelWork.lock()->CalcNodeMatrices();*/
}

void RedDice::Shake(const int _number, const Math::Vector3 _pos, const Math::Vector3 _moveDir, const float _speed, const Math::Vector3 _rotDir)
{
	m_pos = _pos;
	m_moveDir = _moveDir;
	m_moveDir.Normalize();
	m_moveSpeed = _speed;
	m_rotDir = _rotDir;
}
