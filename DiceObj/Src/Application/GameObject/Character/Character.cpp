#include "Character.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"
#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"

#include"../../Scene/SceneManager.h"


void Character::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		//m_spModel->SetModelData("Asset/Models/Robot/Robot.gltf");
		m_spModel->SetModelData("Asset/Models/SkinMeshMan/SkinMeshMan.gltf");
	
		//初期のアニメーションをセットする
		m_spAnimetor = std::make_shared<KdAnimator>();
		m_spAnimetor->SetAnimation(m_spModel->GetAnimation("Walk"));
	}

	m_diceFlg = false;
	m_skillParam = 60;
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float			_moveSpd = 0.05f;
	Math::Vector3	_nowPos	= GetPos();

	Math::Vector3 _moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x =  1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z =  1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	Dice();

	const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		_moveVec = _moveVec.TransformNormal(_moveVec, _spCamera->GetRotationYMatrix());
	}
	_moveVec.Normalize();
	_moveVec *= _moveSpd;
	_nowPos += _moveVec;

	// キャラクターの回転行列を創る
	UpdateRotate(_moveVec);

	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _rotation * Math::Matrix::CreateTranslation(_nowPos);
}

void Character::PostUpdate()
{
	//アニメーションの更新
	m_spAnimetor->AdvanceTime(m_spModel->WorkNodes());
	m_spModel->CalcNodeMatrices();
}

void Character::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}



void Character::UpdateRotate(const Math::Vector3& srcMoveVec)
{
	// 何も入力が無い場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.0f) { return; }

	// キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Backward();

	// 移動方向のベクトル
	Math::Vector3 _targetDir = srcMoveVec;

	_nowDir.Normalize();
	_targetDir.Normalize();

	float _nowAng = atan2(_nowDir.x, _nowDir.z);
	_nowAng = DirectX::XMConvertToDegrees(_nowAng);

	float _targetAng = atan2(_targetDir.x, _targetDir.z);
	_targetAng = DirectX::XMConvertToDegrees(_targetAng);

	// 角度の差分を求める
	float _betweenAng = _targetAng - _nowAng;
	if (_betweenAng > 180)
	{
		_betweenAng -= 360;
	}
	else if (_betweenAng < -180)
	{
		_betweenAng += 360;
	}

	float rotateAng = std::clamp(_betweenAng, -8.0f, 8.0f);
	m_worldRot.y += rotateAng;
}

void Character::Dice()
{
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!m_diceFlg)
			{

				int l_num = m_randGen.GetInt(1, 100);

				std::shared_ptr<Cutin> _cut = std::make_shared<Cutin>();

				if (l_num <= m_skillParam)
				{
					_cut->Set(TEXTUREPASS "Critical.png", SOUNDPASS"Success.wav");
					SceneManager::Instance().AddObject(_cut);
				}
				else
				{
					_cut->Set(TEXTUREPASS "Fumble.png", SOUNDPASS"Fail.wav");
					SceneManager::Instance().AddObject(_cut);
				}

				m_diceFlg = true;
				int l_tens = l_num / TEN;
				if (!m_wpRDice.expired())
				{
					m_wpRDice.lock()->Shake(l_tens, { 0.8f,-0.8f,1.0f }, { -1,1,0 }, 0.025f, { 21,19,62 });
				}
				int l_ones = l_num % TEN;
				if (!m_wpBDice.expired())
				{
					m_wpBDice.lock()->Shake(l_ones, { 1.f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { 28,74,8 });
				}
			}
		}
		else
		{
			m_diceFlg = false;
		}
	}
	else
	{
		m_diceFlg = false;
	}
}
