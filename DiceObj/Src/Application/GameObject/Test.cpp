#include "Test.h"

#include"../main.h"

void Test::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	DirectX::BoundingBox box;
	extents = { 1,1,1 };
	box.Center = {5,1,6};
	box.Extents = { 1,1,1 };

	color = { 0,1,0 };

	DirectX::BoundingSphere sphere;
	sphere.Center = { 5,1,6 };
	sphere.Radius = 1.0f;

	m_brightFlg = false;
	time = 120;

	m_mWorld = Math::Matrix::CreateTranslation(box.Center);

	m_model = std::make_shared<KdModelData>();
	//m_model->Load("Asset/Models/Terrains/R'lyeh/Bridge/Bridge/Bridge.gltf");
	//m_model->Load("Asset/Models/Terrains/R'lyeh/Cathedral/Arch/Arch.gltf");
	m_model->Load("Asset/Models/Terrains/R'lyeh/R'lyeh.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	//m_pCollider->RegisterCollisionShape("Test",box, KdCollider::TypeDamage);
	//m_pCollider->RegisterCollisionShape("Test",sphere, KdCollider::TypeDamage);
	m_pCollider->RegisterCollisionShape("Test",m_model, KdCollider::TypeDamage);
	//m_pCollider->RegisterCollisionShape("Test", { 0,0.5f,0 }, 1, KdCollider::TypeDamage);
}

void Test::Update()
{
	//Application::Instance().m_log.AddLog("Tpost %.0f,%.0f,%.0f\n", m_mWorld.Translation().x, m_mWorld.Translation().y, m_mWorld.Translation().z);

	if (m_brightFlg)
	{
		time--;
		if (time < 0) {
			m_brightFlg = false;
		}
	}

	color = { 0,1,0 };
}

void Test::PostUpdate()
{
	//m_pDebugWire->AddDebugBox(m_mWorld, extents, {}, false, color);
	m_pDebugWire->AddDebugSphere(m_mWorld.Translation(), 1.0f, color);
}

void Test::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Test::DrawBright()
{
	if (!m_brightFlg)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Test::OnHit()
{
	color = { 1,0,0 };
	time = 120;
	m_brightFlg = true;
	Application::Instance().m_log.AddLog("log\n");
}

void Test::Release()
{
	m_model = nullptr;
}
