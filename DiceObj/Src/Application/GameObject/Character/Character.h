#pragma once

class CameraBase;

class DiceBase;

#define TEN	10

#define CRITICAL_RANGE	5
#define FUMBLE_RANGE	96

class Character : public KdGameObject
{
public:

	enum Skill
	{
		None,
		Search,
		Listeing,
		Max,
	};
	
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
	
	void Dice();

private:


	void UpdateRotate(const Math::Vector3& srcMoveVec);


	std::shared_ptr<KdModelWork>		m_spModel		= nullptr;
	std::shared_ptr<KdAnimator>			m_spAnimetor	= nullptr;

	std::weak_ptr<CameraBase>			m_wpCamera;

	std::shared_ptr<KdGameObject>		m_now			= nullptr;

	Math::Vector3						m_worldRot;

	Math::Vector3						m_pos;

	float								m_gravity;

	const float							m_moveSpd=0.08f;

	//ダイス関係
	bool								m_diceFlg = false;
	bool								m_listeingFlg = false;
	
	//技能関係
	int									m_skillParam	= 0;
	Skill								m_skill			= Skill::None;
	float								m_sphereRadius	= 0;
	Math::Vector3						m_boxExtents	= {};
	
	KdRandomGenerator					m_randGen;
};

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/SE/"