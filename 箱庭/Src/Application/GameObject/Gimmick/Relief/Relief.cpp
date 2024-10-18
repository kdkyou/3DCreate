#include "Relief.h"

#include"../../Information/Information.h"

#include"../../Noise/Noise.h"

#include"../../../Scene/SceneManager.h"

void Relief::SetModel(const std::shared_ptr<KdModelData>& model)
{
	m_spModel = model;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Relief", m_spModel, KdCollider::TypeEvent);

	m_fTexture = std::make_shared<KdTexture>();
	m_fTexture->Load(RELIEFPATH"F.png");

	m_cthlhuTex = std::make_shared<KdTexture>();
	m_cthlhuTex->Load("Asset/Textures/GameObject/Apotheosis/Cthlhu.png");

	m_createFlg = false;
}

void Relief::Update()
{
	m_coolTime--;
	if (m_coolTime < 0)
	{
		m_coolTime = 0;
		m_createFlg = false;
	}
}

void Relief::OnHit()
{
	if (!m_createFlg)
	{
		m_createFlg = true;
		m_coolTime = COOL_TIME;
		std::shared_ptr<Information> _info = std::make_shared<Information>();

		std::string _path;
		m_isInfor = false;

		int num = SceneManager::Instance().GetReliefCount();
		switch (num)
		{
		case 0:
			_path = RELIEFPATH"before1.png";
			break;
		case 1:
			_path = RELIEFPATH"known.png";
			m_isInfor = true;
			break;
		case 2:
			_path = RELIEFPATH"before2.png";
			break;
		case 3:
			_path = RELIEFPATH"little.png";
			m_isInfor = true;
			break;
		case 4:
			_path = RELIEFPATH"before3.png";
			break;
		case 5:
			_path = RELIEFPATH"half.png";
			m_isInfor = true;
			break;
		case 6:
			_path = RELIEFPATH"elder.png";
			break;
		case 7:
			_path = RELIEFPATH"before4.png";
			break;
		case 8:
			_path = RELIEFPATH"understand.png";
			m_isInfor = true;
			break;
		case 9:
			_path = RELIEFPATH"before5.png";
			break;
		case 10:
			_path = RELIEFPATH"Per.png";
			m_isInfor = true;
			break;
		default:
			break;
		}
		_info->SetTexture(_path, true);
		SceneManager::Instance().AddObject(_info);
		if (!m_isOnes)
		{
			SceneManager::Instance().AddReliefCount();
			m_isOnes = true;
		}

		if (m_isInfor)
		{
			std::shared_ptr<Noise> noise = std::make_shared<Noise>();
			noise->Init();
			noise->SetParam(m_cthlhuTex, 180);
			SceneManager::Instance().AddNoise(noise);
		}
	}
}

void Relief::OnEncount()
{
	/*m_drawFkeyFlg = true;
	*/
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (!m_createFlg)
		{
			OnHit();
		}
	}
	
}

void Relief::DrawSprite()
{
	if (!m_drawFkeyFlg)return;
	
//	KdShaderManager::Instance().m_spriteShader.DrawTex(m_fTexture, 0, 0);
}
