#pragma once

class Character;

class DiceManager:public KdGameObject
{
public:
	DiceManager(){}
	~DiceManager()override{}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

private:

	std::shared_ptr<KdTexture>	m_skillTex;
	std::shared_ptr<KdTexture>	m_frameTex;

	std::shared_ptr<Character>	m_spChara;

	Math::Vector2				m_skillPos;
	Math::Vector2				m_searchPos;
	Math::Vector2				m_listeingPos;

};
