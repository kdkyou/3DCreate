#include "Relief.h"

#include"../../Information/Information.h"

#include"../../../Scene/SceneManager.h"

void Relief::SetModel(std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Relief", m_spModel, KdCollider::TypeEvent);

	m_fTexture = std::make_shared<KdTexture>();
	m_fTexture->Load(RELIEFPATH"F.png");

}

void Relief::Update()
{
	m_brightTime--;
	if (m_brightTime < 0)
	{
		m_brightTime = 0;
	}

	m_drawFkeyFlg = false;
}

void Relief::OnHit()
{
	std::shared_ptr<Information> _info = std::make_shared<Information>();
	
	std::string _path;
	switch (SceneManager::Instance().GetReliefCount())
	{
	case 0:
		_path = RELIEFPATH"known.png";
		break;
	case 1:
		_path = RELIEFPATH"little.png";
		break;
	case 2:
		_path = RELIEFPATH"half.png";	
		break;
	case 3:
		_path = RELIEFPATH"understand.png";
		break;
	default:
		break;
	}
	_info->SetTexture(_path,true);
	SceneManager::Instance().AddObject(_info);
	SceneManager::Instance().AddReliefCount();

}

void Relief::OnEncount()
{
	m_drawFkeyFlg = true;
	if (GetAsyncKeyState('F'))
	{
		if (!m_createFlg)
		{
			OnHit();
		}
	}
	else
	{
		m_createFlg = false;
	}
}

void Relief::DrawSprite()
{
	if (!m_drawFkeyFlg)return;
	
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_fTexture, 0, 0);
}
