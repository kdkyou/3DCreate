#pragma once

class ActerBase :public KdGameObject
{
public:
	ActerBase() {}
	~ActerBase()override {}


	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

protected:

	std::shared_ptr<KdModelWork>	m_spModelWork = nullptr;
	std::shared_ptr<KdAnimator>		m_spAnimetor = nullptr;

	Math::Vector3					m_pos;
	Math::Vector3					m_move;

};