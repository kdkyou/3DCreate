#include "Gate.h"
#include "../../Character/Player/Character.h"

#include"../../Noise/Noise.h"
#include"../../../Scene/SceneManager.h"

void Gate::Init()
{
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/GameObject/Apotheosis/Gate.png");

	m_polygon->SetScale(5);

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Gate", {}, 3.0f, KdCollider::TypeEvent);

	m_objName = "Gate";

	Math::Vector3 pos = { 52.0f,8.0f,90.0f };

	SetPos(pos);

	//カメラのローカル行列
	Math::Matrix _transMat = Math::Matrix::CreateTranslation({ -7.0f,7.0f,0.0f });
	Math::Matrix _rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	Math::Matrix _rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	m_mlocalCamera = _rotMat * _rotY * _transMat;
}

void Gate::Update()
{
	//std::shared_ptr<Character> _player = m_target;

	//Math::Matrix _playerMat;
	//if (_player)
	//{
	//	_playerMat = _player->GetMatrix();
	//}

	////プレイヤー(カメラ)と同じ軸を代入して方向を合わせる
	//m_mWorld.Backward(_playerMat.Backward());
	//m_mWorld.Up(_playerMat.Up());
	//m_mWorld.Right(_playerMat.Right());

	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 3,3,3 }, 5.0f,{});
}



void Gate::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}


void Gate::SetTarget(const std::shared_ptr<Character>& _target)
{
	m_target = _target;
}

void Gate::OnHit()
{
	/*std::shared_ptr<Noise> noise = std::make_shared<Noise>();
	std::shared_ptr<KdTexture> tex = std::make_shared<KdTexture>();
	tex->Load("Asset/Textures/GameObject/Apotheosis/End.png");
	noise->SetParam(tex, 120, 15, kWhiteColor, false);
	SceneManager::Instance().AddNoise(noise);*/

	KdAudioManager::Instance().StopAllSound();
	SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
}
