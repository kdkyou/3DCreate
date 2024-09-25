#include "TPSCamera.h"

#include"../../../Scene/SceneManager.h"

void TPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	m_iniPos = { -0.f, 1.3f, -3.f };
	m_pos = m_iniPos;
	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(m_iniPos);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
	m_DegAng.y = 90;

	m_mRotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));

	m_mWorld = m_mRotation * m_mLocalPos;

	//被写界深度	  
	//m_spCamera->SetFocus(
	//	m_mWorld.Translation().x,		// ピントの位置
	//	m_mWorld.Translation().x - 30,		//手前のぼかし距離
	//	m_mWorld.Translation().x + 30);		//奥のぼかし距離

	//フォグ(霧)
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
}

void TPSCamera::Update()
{
	/*Math::Vector3 m_move = Math::Vector3::Zero;

	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();

	if (_spTarget)
	{
		Math::Vector3 _vec = _spTarget->GetMatrix().Translation() - m_pos;
		if (_vec.Length() > 17.f)
		{
			int i = _vec.Length();
			m_move = (_spTarget->GetMatrix().Translation() - m_pos);
			m_move.Normalize();
			m_pos += m_iniPos + m_move * Math::Vector3(_spTarget->GetMatrix().Translation() - m_pos).Length() / MOVE_SPEED;
		}

	}


	m_mLocalPos = Math::Matrix::CreateTranslation(m_pos);*/
}

void TPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	if (!(GetAsyncKeyState(VK_LSHIFT)))
	{
		UpdateRotateByMouse();
	}
	m_mRotation = GetRotationMatrix();
	m_mWorld =  m_mLocalPos * m_mRotation  * _targetMat;


	//高さフォグ														↓色	上の上限　下の上限　カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.1f,0.1f,0.3f }, m_mWorld.Translation().y + 70, m_mWorld.Translation().y - 40, 0);

	//// ↓めり込み防止の為の座標補正計算↓
	//// ①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo rayInfo;
	// レイの発射位置を設定
	rayInfo.m_pos = GetPos();

	// レイの発射方向を設定
	rayInfo.m_dir = Math::Vector3::Down;
	// レイの長さを設定
	rayInfo.m_range = 1000.f;
	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1f;
		rayInfo.m_dir = _targetPos - GetPos();
		rayInfo.m_range = rayInfo.m_dir.Length();
		rayInfo.m_dir.Normalize();
	}

	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// ②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj :SceneManager::Instance().GetMapObjList())
	{
		std::shared_ptr<KdGameObject> spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spGameObj->Intersects(rayInfo, &retRayList);

			// ③ 結果を使って座標を補完する
			// レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;
			for (auto& ret : retRayList)
			{
				// レイを遮断しオーバーした長さが
				// 一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}
			if (hit)
			{
				// 何かしらの障害物に当たっている
				Math::Vector3 _hitPos = hitPos;
				_hitPos += rayInfo.m_dir * 0.4f;
				SetPos(_hitPos);
			}
		}
	}
}
