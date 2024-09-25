#include "WeaponBase.h"
#include"../Character/CharacterBase/CharacterBase.h"

void WeaponBase::Update()
{
	//const std::shared_ptr<const CharacterBase> _wpParent = m_wpParent.lock();
	//if (_wpParent)
	//{
	//	//親の行列の取得
	//Math::Matrix _parentMat	 = m_wpParent.lock()->GetMatrix();
	//
	//	//自身の座標行列作成
	//
	//	//ワールド行列に作成
	//m_mWorld =_parentMat;
	//}
}

void WeaponBase::DrawLit()
{
	if (m_spWModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWModel, m_mWorld);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}

}

void WeaponBase::GenerateDepthMapFromLight()
{
	if (m_spWModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spWModel, m_mWorld);
	}

	if (m_spDModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spDModel, m_mWorld);
	}
}


