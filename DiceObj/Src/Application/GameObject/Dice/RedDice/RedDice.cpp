#include "RedDice.h"

void RedDice::Init()
{
	m_pos = {2,0,0};
	m_moveDir = {};
	m_rotDir = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(HALF);
	m_mWorld = _scaleMat * _transMat;

	//初期のアニメーションをセットする
	/*m_spAnimetor = std::make_shared<KdAnimator>();
	if (!m_wpModelWork.expired())
	{
		m_spAnimetor->SetAnimation(m_wpModelWork.lock()->GetAnimation("Drop"));
	}*/
}

void RedDice::Update()
{
	m_pos += m_moveDir;

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(HALF);
	m_mWorld = _scaleMat * _transMat;
}

void RedDice::PostUpdate()
{
	//アニメーションの更新
	/*m_spAnimetor->AdvanceTime(m_wpModelWork.lock()->WorkNodes());
	m_wpModelWork.lock()->CalcNodeMatrices();*/
}

void RedDice::Shake(const int _number)
{

}
