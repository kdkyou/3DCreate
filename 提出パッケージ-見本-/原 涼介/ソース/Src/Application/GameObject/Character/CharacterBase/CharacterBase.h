#pragma once

//キータイプのマクロ
#define UPDOWN		KeyType::Up | KeyType::Down
#define LEFTRIGHT	KeyType::Left | KeyType::Right
#define AROUND		KeyType::Forward | KeyType::Backward

//イージング時間のマクロ
#define ONE_SECOND 1.0f/60.0f
#define TWO_SECOND 1.0f/120.0f

class CharacterBase :public KdGameObject
{
public:

	enum SelectType
	{
		None,
		Break,
		Push,
	};

	enum class EasingType
	{
		Normal,
		In,
		Out,

	};

	enum KeyType	//ビット
	{
		Flat,
		Up			= 1 << 0,		//上
		Down		= 1 << 1,		//下
		Left		= 1 << 2,		//左
		Right		= 1 << 3,		//右
		Forward		= 1 << 4,		//前
		Backward	= 1 << 5,		//後
		Max,
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

