#include "Character.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"
#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"
#include"../Information/Information.h"

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"


void Character::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Probe/Probe.gltf");
	}

	m_gravity = 0;
	m_pos = {};
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	m_diceFlg = false;
	m_skillParam = 70;

	m_sphereRadius = 5.0f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Character::Update()
{
	m_skill = Skill::None;

	Math::Vector3 _moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { _moveVec.x =  1.0f; }
	if (GetAsyncKeyState('A')) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { _moveVec.z =  1.0f; }
	if (GetAsyncKeyState('S')) { _moveVec.z = -1.0f; }

	//if(GetAsyncKeyState('E'))

	Dice();

	if (GetAsyncKeyState('O')) { m_pos = { 212.f,4.8f,-19.f }; }

	const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		_moveVec = _moveVec.TransformNormal(_moveVec, _spCamera->GetRotationYMatrix());
	}
	_moveVec.Normalize();
	_moveVec *= m_moveSpd;
	m_pos += _moveVec;

	m_pos.y -= m_gravity;
	m_gravity += 0.001f;

	// キャラクターの回転行列を創る
	UpdateRotate(_moveVec);

	
	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _rotation * Math::Matrix::CreateTranslation(m_pos);
}

void Character::PostUpdate()
{
	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;		//	当たっていたらtrue


	//レイ判定用に変数を作成
	KdCollider::RayInfo ray;
	//レイの発射位置(座標)を設定
	ray.m_pos = m_pos;		//自分の足元
	//レイの発射方向を設定
	ray.m_dir = Math::Vector3::Down;
	//段差の許容範囲を設定
	float enableStepHigh = 1.5f;
	ray.m_pos.y += enableStepHigh;
	//レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//レイと当たり判定！！
	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(ray, &retList);
	}
	//レイに当たったリストから一番近いオブジェクトを検出
	for (auto& ret : retList)
	{
		//レイを遮断し、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitPos;
			isHit = true;
		}
	}
	if (isHit)
	{
		//地面に当たっている
		m_pos = hitDir + Math::Vector3(0.0f, -0.0f, 0.0f);
		m_gravity = 0.0f;
	}

	retList.clear();

	//地面との判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{0.f,0.5f,0.f};
	_sphereInfo.m_sphere.Radius = 0.5;
	_sphereInfo.m_type = KdCollider::TypeGround;

	//m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius);
	
	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(_sphereInfo, &retList);
	}
	//　球に当たったリストから一番近いオブジェクトを検出
	for (auto& ret : retList)
	{
		//球にめり込んで、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}
	if (isHit)
	{
		//	正規化(長さを1にする)
		//	方向は絶対長さ1
		hitDir.Normalize();
		//	地面に当たっている
		m_pos += hitDir * maxOverLap;
	}
	
	retList.clear();

	//攻撃物との判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.f,0.5f,0.f };
	_sphereInfo.m_sphere.Radius = 0.5;
	_sphereInfo.m_type = KdCollider::TypeDamage;

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr))
		{
			OnHit();
		}
	}
	if (m_pos.y < -2.0f)
	{
		OnHit();
	}

	Judge();

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

void Character::DiceSkill()
{
	int l_num = m_randGen.GetInt(1, 100);

	std::shared_ptr<Cutin> _cut = std::make_shared<Cutin>();

	
	if (l_num <= m_skillParam)
	{
		if (l_num <= CRITICAL_RANGE)
		{
			_cut->Set(TEXTUREPASS "Critical.png", SOUNDPASS"Critical.wav");
			m_sphereRadius = 10.0f;
		}
		else
		{
			_cut->Set(TEXTUREPASS "", SOUNDPASS"Success.wav");
			m_sphereRadius = 5.0f;
		}
	}
	else
	{
		if (l_num >= FUMBLE_RANGE)
		{
			_cut->Set(TEXTUREPASS "Fumble.png", SOUNDPASS"Fumble.wav");
			m_sphereRadius = 0.0f;
			m_skill = Skill::None;
		}
		else
		{
			_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
			m_sphereRadius = 0.0f;
			m_skill = Skill::None;
		}
	}
	SceneManager::Instance().AddObject(_cut);

	std::shared_ptr<BlueDice> _blueDice = std::make_shared<BlueDice>();
	_blueDice->SetModel(AssetRepository::Instance().GetModel("BlueDice"));
	_blueDice->Init();
	_blueDice->SetCamera(m_wpCamera.lock());

	std::shared_ptr<RedDice> _redDice = std::make_shared<RedDice>();
	_redDice->SetModel(AssetRepository::Instance().GetModel("RedDice"));
	_redDice->Init();
	_redDice->SetCamera(m_wpCamera.lock());

	int l_tens = l_num / TEN;
	_redDice->Shake(l_tens, { 0.8f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });
	int l_ones = l_num % TEN;
	_blueDice->Shake(l_ones, { 1.f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });

	SceneManager::Instance().AddObject(_redDice);
	SceneManager::Instance().AddObject(_blueDice);

	SceneManager::Instance().DiceFlgONOFF(false);
}

void Character::SetSkill(const Skill& skill)
{
	m_skill = skill;
	switch (skill)
	{
	case Skill::Search:
		m_skillParam = 70;
		break;
	case Skill::Listeing:
		m_skillParam = 60;
		break;
	default:
		break;
	}
}

void Character::OnHit()
{
	m_pos = {};
}

void Character::Dice()
{
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{

		//SceneManager::Instance().DiceFlgONOFF(true);
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!m_diceFlg)
			{
				m_diceFlg = true;

				int l_num = m_randGen.GetInt(1, 100);

				m_skill = Skill::Search;

				std::shared_ptr<Cutin> _cut = std::make_shared<Cutin>();

				if (l_num <= m_skillParam)
				{
					if (l_num <= CRITICAL_RANGE)
					{
						_cut->Set(TEXTUREPASS "Critical.png", SOUNDPASS"Critical.wav");
						m_sphereRadius = 10.0f;
					}
					else
					{
						_cut->Set(TEXTUREPASS "", SOUNDPASS"Success.wav");
						m_sphereRadius = 5.0f;
					}
				}
				else
				{
					if (l_num >= FUMBLE_RANGE)
					{
						_cut->Set(TEXTUREPASS "Fumble.png", SOUNDPASS"Fumble.wav");
						m_sphereRadius = 0.0f;
						m_skill = Skill::None;
					}
					else
					{
						_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
						m_sphereRadius = 0.0f;
						m_skill = Skill::None;
					}
				}
				SceneManager::Instance().AddObject(_cut);

				std::shared_ptr<BlueDice> _blueDice = std::make_shared<BlueDice>();
				_blueDice->SetModel(AssetRepository::Instance().GetModel("BlueDice"));
				_blueDice->Init();
				_blueDice->SetCamera(m_wpCamera.lock());

				std::shared_ptr<RedDice> _redDice = std::make_shared<RedDice>();
				_redDice->SetModel(AssetRepository::Instance().GetModel("RedDice"));
				_redDice->Init();
				_redDice->SetCamera(m_wpCamera.lock());

				int l_tens = l_num / TEN;
					_redDice->Shake(l_tens, { 0.8f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });
				int l_ones = l_num % TEN;
					_blueDice->Shake(l_ones, { 1.f,-0.8f,1.0f }, { -1,1,0 }, 0.02f, { m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30),m_randGen.GetFloat(1, 30) });

				SceneManager::Instance().AddObject(_redDice);
				SceneManager::Instance().AddObject(_blueDice);
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

void Character::Judge()
{

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;		//	当たっていたらtrue

	//イベント物との判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.f,0.5f,0.f };
	_sphereInfo.m_sphere.Radius = 3.0f;
	_sphereInfo.m_type = KdCollider::TypeEvent;

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr)) {
			obj->OnEncount();
		}
	}

	switch (m_skill)
	{
	case Skill::Search:
		//目星・・・プレイヤーの正面に球判定でアクションが起こせる物を光らせる

		_sphereInfo.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{ 0.f,0.5f,0.f };
		_sphereInfo.m_sphere.Radius = m_sphereRadius;
		_sphereInfo.m_type = KdCollider::TypeEvent;

		//m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kWhiteColor);

		for (auto& obj : SceneManager::Instance().GetGimmickObjList())
		{
			if (obj->Intersects(_sphereInfo, &retList))
			{
				//範囲内のオブジェクトの位置
				Math::Vector3 posDelta = retList.begin()->m_hitPos - m_mWorld.Translation();

				//現在の向いてる方向
				Math::Vector3 nowDir = m_mWorld.Backward();

				//範囲内オブジェクトの角度を算出
				float target_angle = nowDir.Dot(posDelta);

				static float angle = 40;

				if (target_angle < angle)
				{
					obj->OnBright();
				}
				retList.clear();
			}
		}


		break;
	case Skill::Listeing:
		//聞き耳・・・プレイヤー中心で球判定で敵の足音などを判定させる
		_sphereInfo.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{ 0.f,0.5f,0.f };
		_sphereInfo.m_sphere.Radius = m_sphereRadius;
		_sphereInfo.m_type = KdCollider::TypeDamage;

		//m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kWhiteColor);

		for (auto& obj : SceneManager::Instance().GetGimmickObjList())
		{
			if (obj->Intersects(_sphereInfo, nullptr))
			{
				if (!m_listeingFlg)
				{
					m_listeingFlg = true;
					std::shared_ptr<Information> _info = std::make_shared<Information>();
					_info->SetTexture("Asset/Textures/GameObject/Dice/listeing.png");
					SceneManager::Instance().AddObject(_info);
				}
			}
		}
		break;
	default:
		break;
	}
}
