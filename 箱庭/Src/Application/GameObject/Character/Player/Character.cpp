﻿#include "Character.h"

#include "../../../main.h"
#include "../../Camera/CameraBase.h"
#include"../../Cutin/Cutin.h"
#include"../../Information/Information.h"

#include"../../Noise/Noise.h"

#include"../../../Scene/SceneManager.h"

#include"../../../AssetRepository/AssetRepository.h"





void Character::Init()
{
	if (!m_spModelWork)
	{
		m_spModelWork = std::make_shared<KdModelWork>();
		m_spModelWork->SetModelData("Asset/Models/Player/Player.gltf");

	
		m_spAnimetor = std::make_shared<KdAnimator>();
		m_spAnimetor->SetAnimation(m_spModelWork->GetData()->GetAnimation("Idle"), true);
	}

	

	m_gravity = 0;
	m_pos = {};


	Math::Matrix _scale = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
	m_mWorld = _scale * _rotY * Math::Matrix::CreateTranslation(m_pos);
	m_worldRot.y = 0;

	m_sphereRadius = 5.0f;

	m_time = 0;
	m_deathConut = 0;

	m_iniSAN = m_randGen.GetInt(40, 60);
	m_SAN = m_iniSAN;

	m_nextType = SelectType::Push;

	m_tex=KdAssets::Instance().m_textures.GetData("Asset/Textures/GameObject/Apotheosis/Nyarlathotep.png");
	tex=KdAssets::Instance().m_textures.GetData("Asset/Textures/GameObject/Apotheosis/End.png");

	m_objName = "Player";

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//カメラのローカル行列
	Math::Matrix _transMat = Math::Matrix::CreateTranslation({ 0.0f,3.0f,-3.0f });
	Math::Matrix _rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_mlocalCamera = _rotMat * _transMat;

	ChangeActionState(std::make_shared<ActionIdle>());
}

void Character::Update()
{

	CoolTime();

	{
		const std::shared_ptr<const KdGameObject> _spParent = m_wpRideObject.lock();
		Math::Matrix _parentMat = Math::Matrix::Identity;
		if (_spParent)
		{
			_parentMat = _spParent->GetMatrix();
			m_mWorld = m_localMatFromRideObject * _parentMat;

		}
	}
	m_pos = m_mWorld.Translation();

	
	m_gravity += GRAVITY;
	m_pos.y -= m_gravity;

	//各種「状態に応じた」更新処理を実行する
	if (m_nowAction)
	{
		m_nowAction->Update(m_wpChara);
	}

	UpdateCollision();


	const KdModelWork::Node* _pNode = GetModelWork()->FindWorkNode("CameraPoint");
	if (_pNode)
	{
		m_mlocalCamera = _pNode->m_worldTransform;
	}


	

	
//	KdAudioManager::Instance().SetListnerMatrix(m_mWorld);
}

void Character::PostUpdate()
{
	m_spAnimetor->AdvanceTime(m_spModelWork->WorkNodes());

	m_spModelWork->CalcNodeMatrices();

}


void Character::UpdateRotate(const Math::Vector3& srcMoveVec)
{

	// 何も入力が無い場合は処理しない
	if (srcMoveVec.LengthSquared() == 0.0f) { return; }

	// キャラの正面方向のベクトル
	Math::Vector3 _nowDir = GetMatrix().Forward();

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

void Character::UpdateCollision()
{
	m_wpRideObject.reset();

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir = {};	//当たった方向
	bool isHit = false;		//	当たっていたらtrue

	//レイ判定用に変数を作成
	KdCollider::RayInfo ray;
	//レイの発射位置(座標)を設定
	ray.m_pos = GetPos();		//自分の足元
		//レイの発射方向を設定
	ray.m_dir = Math::Vector3::Down;
	//段差の許容範囲を設定
	float enableStepHigh = 1.0f;
	ray.m_pos.y += enableStepHigh;
	//レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

//	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//マップリストのレイと当たり判定！！
	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(ray, &retList);
	}

	int i = 0;
	//ギミックリストのレイと判定
	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(ray, &retList))
		{
			if (obj->IsRideable())
			{
				m_wpRideObject = obj;
			}
		}
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
		m_pos = hitDir;
		m_gravity = 0.0f;
		SetPos(m_pos);

		//プレイヤーが何かに乗っていれば
		//乗り物から見たプレイヤーのローカル行列を保存

		//ex 逆行列の取得方法	※プレイヤーの場合
		// 
		//乗り物の逆行列の取得
		const std::shared_ptr<const KdGameObject> _spParent = m_wpRideObject.lock();
		Math::Matrix _parentInvertMat = Math::Matrix::Identity;
		if (_spParent)
		{
			_parentInvertMat = _spParent->GetMatrix().Invert();

			m_worldRot.y += _spParent->GetAddNumber();
		}


		//乗り物から見たプレイヤーのローカル行列作成
		m_localMatFromRideObject = m_mWorld * _parentInvertMat;
	}

	//初期化
	retList.clear();
	maxOverLap = 0.f;
	hitDir = {};
	isHit = false;

	//球判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.0f,1.0f,0.0f };
	_sphereInfo.m_sphere.Radius = 0.4f;
	_sphereInfo.m_type = KdCollider::TypeGround;

//	m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius);

	//マップリストの地面との判定
	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(_sphereInfo, &retList);
	}
	//ギミックリストの地面判定
	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
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
		SetPos(m_pos);
	}

	//イベント関連
	Judge();

	//攻撃物関連
	Damage();

}

void Character::OnHit()
{
	Math::Vector3 _vec = {};
	SetPos(_vec);
	m_deathConut++;
	m_SAN -= m_deathConut;
	float num = 1.0f - (float)m_SAN / (float)m_iniSAN;

	if (m_SAN <= 0)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		return;
	}

	m_color = Math::Vector3{ 1.0f,1.0f - num,1.0f - num };
	Math::Color colr = Math::Color{ 1.0f,1.0f - num,1.0f - num,1.0f };

	std::shared_ptr<Noise> noise = std::make_shared<Noise>();
	noise->SetParam(m_tex, TEN * m_deathConut, 100, colr);
	SceneManager::Instance().AddNoise(noise);


}

void Character::CoolTime()
{
	m_time--;
	if (m_time < 0)
	{
		m_time = 0;
	}
}

void Character::Judge()
{

	KdCollider::SphereInfo _sphereInfo;
	
	//イベント物との判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.f,0.5f,0.f };
	_sphereInfo.m_sphere.Radius = 6.0f;
	_sphereInfo.m_type = KdCollider::TypeEvent;

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr)) {
			obj->OnEncount();
		}
	}

}

void Character::Damage()
{
	KdCollider::SphereInfo _sphereInfo;
	//攻撃物との判定
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.f,0.6f,0.f };
	_sphereInfo.m_sphere.Radius = 0.5;
	_sphereInfo.m_type = KdCollider::TypeDamage;

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr))
		{
			OnHit();
		}
	}

	for (auto& obj : SceneManager::Instance().GetObjList())
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
}

void Character::HitJudge()
{

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;

	Math::Matrix nodeMat = Math::Matrix::Identity;

	const KdModelWork::Node* _pNode = GetModelWork()->FindWorkNode("RightPoint");
	if (_pNode)
	{
		nodeMat = _pNode->m_worldTransform;
	}
	Math::Matrix mat = nodeMat * m_mWorld;

	//イベント物との判定
	_sphereInfo.m_sphere.Center = mat.Translation();
	_sphereInfo.m_sphere.Radius = 0.4f;
	_sphereInfo.m_type = KdCollider::TypeEvent;

//	m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kRedColor);

	for (auto& obj : SceneManager::Instance().GetGimmickObjList())
	{
		if (obj->Intersects(_sphereInfo, nullptr)) {
			obj->OnHit();
		}
	}
}

Math::Vector3 Character::Accelerate(UINT srcMoveKey)
{
	// TODO: return ステートメントをここに挿入します
		//初期化
	static UINT keyData = KeyType::Flat;
	static EasingType easingType = EasingType::Normal;
	static float easingVal = 0.0f;

	UINT key = keyData;


	//入力されたキーを格納(キーが入っている場合)
	if (srcMoveKey != KeyType::Flat)
	{
		//イージングの値設定
		//入力したキーデータが保管しているデータと違う時
		//Inのイージングを設定
		if (srcMoveKey != keyData)
		{
			easingVal = 0.0f;
			easingType = EasingType::SlowIn;
		}

		key |= srcMoveKey;
		//更に入力したデータが反対になるものの場合
		//Outのイージングを設定
//		if (easing & EasingType::None)
		if (key & UPDOWN || key & LEFTRIGHT || key & AROUND)
		{
			easingVal = 1.0f;
			easingType = EasingType::Out;
		}
		//キーデータ格納
		keyData = srcMoveKey;
	}
	else
	{
		//保存されたキーデータがあるとき
		if (keyData != KeyType::Flat)
		{
			//イージングの値設定(アウト)
			if (easingType == EasingType::Normal)
			{
				easingVal = 1.0f;
				easingType = EasingType::Out;
			}
		}
	}

	Math::Vector3 vec = Math::Vector3::Zero;


	//入力したキーデータのベクトル設定
	if (keyData & KeyType::Up)
	{
		vec.y = 1;
	}
	if (keyData & KeyType::Down)
	{
		vec.y = -1;
	}
	if (keyData & KeyType::Left)
	{
		vec.x = -1;
	}
	if (keyData & KeyType::Right)
	{
		vec.x = 1;
	}
	if (keyData & KeyType::Forward)
	{
		vec.z = 1;
	}
	if (keyData & KeyType::Backward)
	{
		vec.z = -1;
	}

	//カメラが向いてる方向に修正
	const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		vec = vec.TransformNormal(vec, _spCamera->GetRotationYMatrix());
	}

	vec.Normalize();

	Math::Vector3 moveSpd = Math::Vector3::Zero;

	//加減速イージング処理
	switch (easingType)
	{
	case CharacterBase::EasingType::SlowIn:
		moveSpd = Math::Vector3(m_maxVec * (1 - cos((easingVal * DirectX::XM_PI) * 0.3f)));
		easingVal += TWO_SECOND;
		if (easingVal > 1.0f)
		{
			easingVal = 1.0f;
			easingType = EasingType::Normal;
		}
		break;
	case CharacterBase::EasingType::Out:
		moveSpd = Math::Vector3(m_maxVec * (sin((easingVal * DirectX::XM_PI) * 0.3f)));
		easingVal -= HALF_SECOND;
		if (easingVal < 0.0f)
		{
			easingVal = 0.0f;
			easingType = EasingType::Normal;
			keyData = KeyType::Flat;
		}
		break;
	default:

		break;
	}

	m_moveVec = vec;

	Math::Vector3 spd = vec * moveSpd;

	return spd;

}

//void Character::UpdateRotateByMouse()
//{
//	// マウスでカメラを回転させる処理
//	POINT _nowPos;
//	GetCursorPos(&_nowPos);
//
//	POINT _mouseMove{};
//	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
//	_mouseMove.y = _nowPos.y - m_FixMousePos.y;
//
//	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
//
//	// 実際にカメラを回転させる処理(0.15はただの補正値)
//	m_DegAng.x += _mouseMove.y * 0.10f;
//	m_DegAng.y += _mouseMove.x * 0.10f;
//
//	// 回転制御
//	m_DegAng.x = std::clamp(m_DegAng.x, -45.f, 45.f);
////	m_DegAng.y = std::clamp(m_DegAng.y, -50.f, 50.f);
//}

/*void Character::DiceSkill()
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

}*/

//void Character::SetSkill(const Skill& skill)
//{
//	m_skill = skill;
//	switch (skill)
//	{
//	case Skill::Search:
//		m_skillParam = 70;
//		break;
//	case Skill::Listeing:
//		m_skillParam = 60;
//		break;
//	default:
//		break;
//	}
//}

/*switch (m_skill)
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
			Math::Vector3 posDelta = retList.begin()->m_hitPos - m_pos;

			//現在の向いてる方向
			Math::Vector3 nowDir = m_mWorld.Backward();

			if (m_wpCamera.expired() != true)
			{
				nowDir = m_wpCamera.lock()->GetMatrix().Backward();
			}

			//範囲内オブジェクトの角度を算出
			float d = nowDir.Dot(posDelta);
			//丸め誤差使用
			d = std::clamp(d, -1.0f, 1.0f);
			//ラジアン角をデグリー角に変更
			float targetAngle = DirectX::XMConvertToDegrees(acos(d));

			static float angle = 30;

			//角度が範囲内かどうか
			if (targetAngle < angle)
			{
				obj->OnBright();
				//KdShaderManager::Instance().WorkAmbientController()
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

	for (auto& obj : SceneManager::Instance().GetObjList())
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
}*/

/*void Character::Dice()
{
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (!m_diceFlg)
		{
			m_diceFlg = true;

			SetSkill(Skill::Search);

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
					m_moveLevel = 0.5f;
					m_time = PENALTH;
				}
				else
				{
					_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
					m_sphereRadius = 0.0f;
					m_skill = Skill::None;
					m_moveLevel = 0.2f;
					m_time = PENALTH;
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

		return;
	}

	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (!m_diceFlg)
		{
			m_diceFlg = true;

			SetSkill(Skill::Listeing);

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
					m_moveLevel = 0.6f;
					m_time = PENALTH;
				}
				else
				{
					_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
					m_sphereRadius = 0.0f;
					m_skill = Skill::None;
					m_moveLevel = 0.3f;
					m_time = PENALTH;
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
		return;
	}
	else
	{
		m_diceFlg = false;
	}


}
*/

//ここからステートパターン関係
void Character::ChangeActionState(std::shared_ptr<ActionStateBase> nextAction)
{
	if (m_nowAction)m_nowAction->Exit(m_wpChara);
	m_nowAction = nextAction;
	m_nowAction->Enter(m_wpChara);
}

void Character::ActionIdle::Enter(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->SetAnimation(spCharacter->m_spModelWork->GetData()->GetAnimation("Idle"));
}

void Character::ActionIdle::Update(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;

	bool isMove = false;

	if (GetAsyncKeyState('W') ||
		GetAsyncKeyState('A') ||
		GetAsyncKeyState('S') ||
		GetAsyncKeyState('D')) {
		isMove = true;
	}
	if (isMove) {
		spCharacter->ChangeActionState(std::make_shared<ActionWalk>());
		return;
	}

	bool isTouch = false;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		isTouch = true;
	}

	if (isTouch) {
		spCharacter->ChangeActionState(std::make_shared<ActionTouch>());
		return;
	}

	// キャラクターのワールド行列を創る処理;
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(spCharacter->m_worldRot.y));
	spCharacter->m_mWorld = _rotation * Math::Matrix::CreateTranslation(spCharacter->m_pos);
}

void Character::ActionIdle::Exit(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->IsAnimationEnd();
}

void Character::ActionWalk::Enter(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->SetAnimation(spCharacter->m_spModelWork->GetData()->GetAnimation("Walk"));
}

void Character::ActionWalk::Update(std::weak_ptr<Character>& character)
{
	Math::Vector3 _moveVec = Math::Vector3::Zero;
	UINT key = KeyType::Flat;
	const std::shared_ptr<Character>spCharacter = character.lock();

	if (!spCharacter)return;
	Math::Vector3 _nowPos = spCharacter->m_pos;
	Math::Vector3 moveSpd = Math::Vector3::Zero;


	if (GetAsyncKeyState('D') & 0x8000) {
		key = key | KeyType::Right;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		key = key | KeyType::Left;
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		key = key | KeyType::Forward;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		key = key | KeyType::Backward;
	}

	bool isTouch = false;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		isTouch = true;
	}

	if (isTouch)
	{
		spCharacter->ChangeActionState(std::make_shared<ActionTouch>());
	}

	//移動中に何も入力がなければ待機に移行
	if (key == Flat) {
		spCharacter->ChangeActionState(std::make_shared<ActionWalkEnd>());
		return;
	}
	else
	{
		moveSpd = spCharacter->Accelerate(key);
		_nowPos += moveSpd;
	}

	spCharacter->UpdateRotate(moveSpd);

	// キャラクターのワールド行列を創る処理;
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(spCharacter->m_worldRot.y));
	spCharacter->m_mWorld = _rotation * Math::Matrix::CreateTranslation(_nowPos);
}

void Character::ActionWalk::Exit(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->IsAnimationEnd();
}

void Character::ActionTouch::Enter(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->SetAnimation(spCharacter->m_spModelWork->GetData()->GetAnimation("Touch"),false);
}

void Character::ActionTouch::Update(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	{
		spCharacter->HitJudge();
	}

	if (spCharacter->m_spAnimetor->IsAnimationEnd())
	{
		spCharacter->ChangeActionState(std::make_shared<ActionIdle>());
		return;
	}

	// キャラクターのワールド行列を創る処理;
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(spCharacter->m_worldRot.y));
	spCharacter->m_mWorld = _rotation * Math::Matrix::CreateTranslation(spCharacter->m_pos);

}

void Character::ActionTouch::Exit(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->IsAnimationEnd();
}

void Character::ActionWalkEnd::Enter(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->SetAnimation(spCharacter->m_spModelWork->GetData()->GetAnimation("Idle"));
}

void Character::ActionWalkEnd::Update(std::weak_ptr<Character>& character)
{
	UINT key = KeyType::Flat;
	const std::shared_ptr<Character>spCharacter = character.lock();

	if (!spCharacter)return;

	if (GetAsyncKeyState('D') & 0x8000) {
		key = key | KeyType::Right;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		key = key | KeyType::Left;
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		key = key | KeyType::Forward;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		key = key | KeyType::Backward;
	}

	bool isTouch = false;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		isTouch = true;
	}

	if (isTouch)
	{
		spCharacter->ChangeActionState(std::make_shared<ActionTouch>());
	}

	//移動中に何も入力がなければ待機に移行
	if (key == Flat) {
		spCharacter->ChangeActionState(std::make_shared<ActionIdle>());
		return;
	}
}

void Character::ActionWalkEnd::Exit(std::weak_ptr<Character>& character)
{
	const std::shared_ptr<Character>spCharacter = character.lock();
	if (!spCharacter)return;
	spCharacter->m_spAnimetor->IsAnimationEnd();
}
