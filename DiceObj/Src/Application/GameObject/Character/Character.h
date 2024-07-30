#pragma once

class CameraBase;

class DiceBase;

#define TEN	10

#define CRITICA_LRANGE	5
#define FUMBLE_RANGE	96

class Character : public KdGameObject
{
public:
	Character()							{}
	~Character()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;
	void DrawLit()			override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

	void SetDice(const std::shared_ptr<DiceBase>& _red, const std::shared_ptr<DiceBase>& _blue)
	{
		m_wpRDice = _red;
		m_wpBDice = _blue;
	}

private:

	enum DiceJudge
	{
		None,
		Success,
		Fail,
		Max,
	};

	void UpdateRotate(const Math::Vector3& srcMoveVec);

	void Dice();

	std::shared_ptr<KdModelWork>		m_spModel		= nullptr;
	std::shared_ptr<KdAnimator>			m_spAnimetor	= nullptr;

	std::weak_ptr<CameraBase>			m_wpCamera;

	std::weak_ptr<DiceBase>				m_wpRDice;
	std::weak_ptr<DiceBase>				m_wpBDice;

	Math::Vector3						m_worldRot;

	//ダイス関係
	bool								m_diceFlg;
	int									m_skillParam	= 0;
	DiceJudge							m_judge			= DiceJudge::None;

	KdRandomGenerator					m_randGen;
};

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/"