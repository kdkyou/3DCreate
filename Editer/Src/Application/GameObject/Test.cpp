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

	m_mWorld = Math::Matrix::CreateTranslation(box.Center);

	Application::Instance().m_log.AddLog("create\n");
}

void Test::Update()
{
	//Application::Instance().m_log.AddLog("Tpost %.0f,%.0f,%.0f\n", m_mWorld.Translation().x, m_mWorld.Translation().y, m_mWorld.Translation().z);

	color = { 0,1,0 };
}

void Test::PostUpdate()
{
	m_pDebugWire->AddDebugBox(m_mWorld, extents, {}, false, color);
	//m_pDebugWire->AddDebugSphere(m_mWorld.Translation(), 1.0f, color);
}

void Test::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Test::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
}

void Test::OnHit()
{
	color = { 1,0,0 };
	Application::Instance().m_log.AddLog("log\n");
}

void Test::Release()
{
	m_spModel = nullptr;
}
