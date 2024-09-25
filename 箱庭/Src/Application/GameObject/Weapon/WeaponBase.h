#pragma once

class CharacterBase;

class WeaponBase :public KdGameObject
{
public:
	WeaponBase(){}
	virtual ~WeaponBase()override{}

	virtual void Update()override;

	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void SetParent(const std::shared_ptr<CharacterBase>& _parent)
	{
		m_wpParent = _parent;
	}



protected:

	//モデル情報
	std::shared_ptr<KdModelWork> m_spWModel = nullptr;
	std::shared_ptr<KdModelData> m_spDModel = nullptr;

	//親(持ち主)の情報
	std::weak_ptr<CharacterBase>	m_wpParent;

	Math::Matrix _parentMat;
	Math::Matrix m_parentAttachMat;
	
};