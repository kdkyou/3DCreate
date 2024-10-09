#pragma once

class CharacterBase :public KdGameObject
{
public:

	enum SelectType
	{
		None,
		Break,
		Push,
	};

	CharacterBase() {}
	~CharacterBase()override {}


	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	const SelectType GetType()const { return m_type; }
	const SelectType GetNextType()const { return m_nextType; }

	const std::shared_ptr<KdModelWork> GetModelWork()const { return m_spModelWork; }
	
	void SetRideObject(const std::shared_ptr<KdGameObject>& _ride) { m_wpRideObject = _ride; }

protected:
	std::shared_ptr<KdAnimator>		m_spAnimetor = nullptr;

	std::shared_ptr<KdModelWork>	m_spModelWork = nullptr;

	std::weak_ptr<KdGameObject>m_wpRideObject;		//乗っているオブジェクト
	Math::Matrix m_localMatFromRideObject;			//乗っているオブジェクトからのローカル行列


	Math::Vector3					m_pos;
	Math::Vector3					m_move;

	SelectType						m_type = SelectType::None;
	SelectType						m_nextType = SelectType::None;

};