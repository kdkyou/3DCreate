﻿#pragma once

#include"../CharacterBase/CharacterBase.h"

class CameraBase;

class DiceBase;

#define TEN	10

#define CRITICAL_RANGE	5
#define FUMBLE_RANGE	96
#define PENALTH 		120


class Character : public CharacterBase
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

	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}
	
	void DiceSkill();
	void SetSkill(const Skill& skill);


	void OnHit()override;

private:

	void CoolTime();

	void Dice();

	void Judge();

	void UpdateRotate(const Math::Vector3& srcMoveVec);

	
	std::weak_ptr<CameraBase>			m_wpCamera;

	std::shared_ptr<KdGameObject>		m_now			= nullptr;

	Math::Vector3						m_worldRot;
	Math::Vector3						m_color;

	std::shared_ptr<KdTexture> m_tex = nullptr;

	int									m_deathConut;

	float								m_ajustHeight = 0.5f;

	float								m_gravity		= 0;

	
	const float							m_moveSpd=0.1f;
	float								m_moveLevel = 1;

	int									m_time			= 0;

	bool								m_controlKey = false;

	float								m_sphereRadius	= 0;
	
	int									m_SAN = 0;

	//ダイス関係
	bool								m_diceFlg = false;
	bool								m_listeingFlg = false;
	
	//技能関係
	int									m_skillParam	= 0;
	Skill								m_skill			= Skill::None;
	Math::Vector3						m_boxExtents	= {};
	
	KdRandomGenerator					m_randGen;
};

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/SE/"