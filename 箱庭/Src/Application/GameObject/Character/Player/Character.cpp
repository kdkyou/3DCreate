#include "Character.h"

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
		m_spModelWork->SetModelData("Asset/Models/Probe/Probe.gltf");

		m_spAnimetor = std::make_shared<KdAnimator>();
	}

	m_gravity = 0;
	m_pos = {};
	m_pos.y += m_ajustHeight;


	Math::Matrix _scale = Math::Matrix::CreateScale(1.0f);
	Math::Matrix _rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mWorld = _scale * _rotY * Math::Matrix::CreateTranslation(m_pos);

	m_diceFlg = false;
	m_skillParam = 70;

	m_sphereRadius = 5.0f;

	m_moveLevel = 1;
	m_time = 0;
	m_deathConut = 0;

	m_nextType = SelectType::Break;

	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/GameObject/Apotheosis/Nyarlathotep.png");

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Character::Update()
{
	m_skill = Skill::None;


	CoolTime();

	{
		const std::shared_ptr<const KdGameObject> _spParent = m_wpRideObject.lock();
		Math::Matrix _parentMat = Math::Matrix::Identity;
		if (_spParent)
		{
			_parentMat = _spParent->GetMatrix();
			m_mWorld = m_localMatFromRideObject *_parentMat;
		}
	}
	m_pos = m_mWorld.Translation();

	Math::Vector3 _moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState('D') & 0x8000) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W') & 0x8000) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { _moveVec.z = -1.0f; }
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if (m_type == SelectType::None)
		{
			m_spAnimetor->SetAnimation(m_spModelWork->GetData()->GetAnimation("Action"), false);
			m_type = m_nextType;
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_controlKey)
		{
			if (m_nextType == SelectType::Break)
			{
				m_controlKey = true;
				m_nextType = SelectType::Push;
			}
			else
			{
				m_controlKey = true;
				m_nextType = SelectType::Break;
			}
		}
		
	}
	else
	{
		m_controlKey = false;
	}


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


	// キャラクターのワールド行列を創る処理;
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _rotation * Math::Matrix::CreateTranslation(m_pos);


	KdShaderManager::Instance().WorkAmbientController().SetConeLight(
		m_pos + Math::Vector3{ 0,1,0 },
		m_mWorld.Backward(),
		10,
		DirectX::XMConvertToRadians(30),
		{ 1,1.5f,2.0f }
	);

}

void Character::PostUpdate()
{
	m_spAnimetor->AdvanceTime(m_spModelWork->WorkNodes());
	
	m_wpRideObject.reset();

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir = {};	//当たった方向
	bool isHit = false;		//	当たっていたらtrue


	//レイ判定用に変数を作成
	KdCollider::RayInfo ray;
	//レイの発射位置(座標)を設定
	ray.m_pos = m_pos;		//自分の足元
	ray.m_pos.y -= m_ajustHeight;
 	//レイの発射方向を設定
	ray.m_dir = Math::Vector3::Down;
	//段差の許容範囲を設定
	float enableStepHigh = 1.0f;
	ray.m_pos.y += enableStepHigh;
	//レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir,ray.m_range);

	//マップリストのレイと当たり判定！！
	for (auto& obj : SceneManager::Instance().GetMapObjList())
	{
		obj->Intersects(ray, &retList);
	}
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
		m_pos =hitDir;
		m_pos.y += m_ajustHeight;
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
	_sphereInfo.m_sphere.Center = m_pos + Math::Vector3{ 0.0f,0.3f,0.0f };
	_sphereInfo.m_sphere.Radius = 0.3f;
	_sphereInfo.m_type = KdCollider::TypeGround;

	m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius);

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

	Judge();


	if (m_spAnimetor->IsAnimationEnd())
	{
		m_type = SelectType::None;
	}

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
	Math::Vector3 _vec = { 0,m_ajustHeight,0 };
	SetPos(_vec);
	m_deathConut++;

	Math::Color colr = Math::Color{ 1.0f + 0.05f * m_deathConut,1.0f,1.0f,1.0f };

	std::shared_ptr<Noise> noise = std::make_shared<Noise>();
	noise->SetParam(m_tex,TEN*m_deathConut,100,colr);
	SceneManager::Instance().AddNoise(noise);
}

void Character::CoolTime()
{
	m_time--;
	if (m_time < 0)
	{
		m_time = 0;
		m_moveLevel = 1.f;
	}
}

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

void Character::Judge()
{

	KdCollider::SphereInfo _sphereInfo;
	std::list<KdCollider::CollisionResult> retList;

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
}
