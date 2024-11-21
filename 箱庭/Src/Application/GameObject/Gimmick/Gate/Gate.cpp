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
	Math::Matrix _rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45)) * Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	Math::Matrix _transMat = Math::Matrix::CreateTranslation({ -7.0f,7.0f,0.0f });
	m_mlocalCamera = _rotMat * _transMat;
}


void Gate::Update()
{
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
	KdAudioManager::Instance().StopAllSound();
	SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
}
