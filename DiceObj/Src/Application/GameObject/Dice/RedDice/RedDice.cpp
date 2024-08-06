#include "RedDice.h"

#include"../../../main.h"

void RedDice::Init()
{
	m_pos = { 0.2,-0.0f,1.0f };
	m_moveDir = {};
	m_rotDir = {};
	m_rot = {};
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mScaleMat = Math::Matrix::CreateScale(RFONE);
	m_mRotMat = Math::Matrix::CreateFromYawPitchRoll(m_rot);
	m_mWorld = m_mScaleMat*m_mRotMat * _transMat;

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
	switch (_number)
	{
	case 0:
		m_DecidedRot = { 6,5,0 };
		break;
	case 1:
		m_DecidedRot = {2.5f,0.8f,0};
		break;
	case 2:
		m_DecidedRot = { 159,305,28 };
		break;
	case 3:
		m_DecidedRot = { 3.5f,3.f,0 };
		break;
	case 4:
		m_DecidedRot = { 11,234,65 };
		break;
	case 5:
		m_DecidedRot = { 158,103,60 };
		break;
	case 6:
		m_DecidedRot ={ 6,0,0 };
		break;
	case 7:
		m_DecidedRot = { 357,7.5f,0 };
		break;
	case 8:
		m_DecidedRot = { 336,288,71 };
		break;
	case 9:
		m_DecidedRot = { 0,10,1 };
		break;
	default:
		m_DecidedRot = { 6,5,0 };
		break;
	}
	m_pos = _pos;
	m_moveDir = _moveDir;
	m_moveDir.Normalize();
	m_moveSpeed = _speed;
	m_rotDir = _rotDir;
	m_showFrame = 60;
}
