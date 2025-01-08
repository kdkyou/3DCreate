#pragma once

#include"../CharacterBase/CharacterBase.h"

class CameraBase;

class DiceBase;

constexpr int TEN = 10;

constexpr int CRITICAL_RANGE = 5;
constexpr int FUMBLE_RANGE = 96;
constexpr int PENALTH = 120;

class Character : public CharacterBase
{
public:
	
	Character()							{}
	~Character()			override	{}

	void Init()				override;
	void Update()			override;
	void PostUpdate()		override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

	void OnHit()override;

private:

	void CoolTime();

	void Judge();

	Math::Vector3 Accelerate(UINT srcMoveKey);

	void UpdateRotate(const Math::Vector3& srcMoveVec);


	
	std::weak_ptr<CameraBase>			m_wpCamera;

	Math::Vector3						m_worldRot;
	Math::Vector3						m_color;

	std::shared_ptr<KdTexture> m_tex = nullptr;
	std::shared_ptr<KdTexture> tex = nullptr;



	int									m_deathConut = 0;

	float								m_ajustHeight = 0.5f;

	float								m_gravity		= 0;

	float								m_rotY = 0.0f;
	
	Math::Vector3						m_moveVec = Math::Vector3::Zero;
	const Math::Vector3					m_maxVec = {0.15f,0.15f,0.15f};

	const float							m_acceleration = 0.05f;
	
	int									m_time			= 0;

	bool								m_controlKey = false;

	float								m_sphereRadius	= 0;
	
	int									m_SAN = 0;
	int									m_iniSAN = 0;


	
	KdRandomGenerator					m_randGen;
};

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/SE/"