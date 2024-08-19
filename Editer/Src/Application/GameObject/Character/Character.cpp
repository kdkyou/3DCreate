#include "Character.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"
#include"../Dice/BlueDice/BlueDice.h"
#include"../Dice/RedDice/RedDice.h"
#include"../Cutin/Cutin.h"

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"


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

	m_sphereRadius = 2.0f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Character::Update()
{
	m_skill = Skill::None;

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

	//Application::Instance().m_log.AddLog("post %.0f,%.0f,%.0f",m_mWorld.Translation().x, m_mWorld.Translation().y, m_mWorld.Translation().z);


	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));
	m_mWorld = _rotation * Math::Matrix::CreateTranslation(_nowPos);
}

void Character::PostUpdate()
{
	//アニメーションの更新
	m_spAnimetor->AdvanceTime(m_spModel->WorkNodes());
	m_spModel->CalcNodeMatrices();

	KdCollider::BoxInfo _boxInfo;

	_boxInfo.m_Abox.Center = m_mWorld.Translation();
	_boxInfo.m_Abox.Extents = { 1,1,1 };
	_boxInfo.m_type = KdCollider::TypeDamage;

	m_pDebugWire->AddDebugBox(m_mWorld, _boxInfo.m_Abox.Extents);

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(_boxInfo, nullptr))
		{
			obj->OnHit();
		}
	}

	//球判定
	KdCollider::SphereInfo _sphereInfo;
	//結果を格納する
	std::list<KdCollider::CollisionResult> retSphereList;
	float maxOverLap = 0;	//	はみ出た球の長さ
	Math::Vector3 hitDir;	//当たった方向
	bool isHit = false;		//	当たっていたらtrue
	switch (m_skill)
	{
	case Skill::Search:
		//目星・・・プレイヤーの正面に球判定でアクションが起こせる物を光らせる

		_sphereInfo.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{0.f,0.5f,0.f};
		_sphereInfo.m_sphere.Radius = m_sphereRadius;
		_sphereInfo.m_type = KdCollider::TypeDamage;

		m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kWhiteColor);

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(_sphereInfo, &retSphereList);
		}
		//　球に当たったリストから一番近いオブジェクトを検出
		
		for (auto& ret : retSphereList)
		{
			//if (retSphereList.size() == 0)return;

			//範囲内のオブジェクトの位置
			Math::Vector3 posDelta = ret.m_hitPos - m_mWorld.Translation();

			//現在の向いてる方向
			Math::Vector3 nowDir = m_mWorld.Backward();

			//範囲内オブジェクトの角度を算出
			float target_angle = nowDir.Dot(posDelta);

			static float angle = 25;

			if (target_angle < angle)
			{
				//障害物があるかどうか
				/*KdCollider::RayInfo rayInfo;
				rayInfo.m_pos = m_mWorld.Translation();
				rayInfo.m_dir = nowDir;
				rayInfo.m_range = 1.f;
				rayInfo.m_type = KdCollider::TypeBump;*/
				Application::Instance().m_log.AddLog("search\n");
				
			}
		}
		
		break;
	case Skill::Listeing:
		//聞き耳・・・プレイヤー中心で球判定で敵の足音などを判定させる
		_sphereInfo.m_sphere.Center = m_mWorld.Translation() + Math::Vector3{ 0.f,0.5f,0.f };
		_sphereInfo.m_sphere.Radius = m_sphereRadius;
		_sphereInfo.m_type = KdCollider::TypeDamage;

		m_pDebugWire->AddDebugSphere(_sphereInfo.m_sphere.Center, _sphereInfo.m_sphere.Radius, kWhiteColor);

		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(_sphereInfo, &retSphereList);
		}
		//　球に当たったリストから一番近いオブジェクトを検出

		for (auto& ret : retSphereList)
		{
			
				Application::Instance().m_log.AddLog("listeing\n");
		}


		break;
	default:
		break;
	}
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
				m_diceFlg = true;

				int l_num = m_randGen.GetInt(1, 100);

				Application::Instance().m_log.AddLog("num %d\n", l_num);

				if (m_randGen.GetInt(0, 1)==1)
				{
					m_skill = Skill::Search;
				}
				else
				{
					m_skill = Skill::Listeing;
				}

				std::shared_ptr<Cutin> _cut = std::make_shared<Cutin>();

				if (l_num <= m_skillParam)
				{
					if (l_num <= CRITICAL_RANGE)
					{
						_cut->Set(TEXTUREPASS "Critical.png", SOUNDPASS"Critical.wav");
					}
					else
					{
						_cut->Set(TEXTUREPASS "", SOUNDPASS"Success.wav");
					}
				}
				else
				{
					if (l_num >= FUMBLE_RANGE)
					{
						_cut->Set(TEXTUREPASS "Fumble.png", SOUNDPASS"Fumble.wav");
					}
					else
					{
						_cut->Set(TEXTUREPASS "", SOUNDPASS"Fail.wav");
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
