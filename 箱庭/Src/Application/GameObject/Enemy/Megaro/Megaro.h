#pragma once

#include"../../Gimmick/GimmickBase/GimmickBase.h"

#define MOVE_FRAME 600

class Character;

class Megaro:public GimmickBase
{
public:
	Megaro(){}
	~Megaro()override{}

	void Update()override;

	void SetModel(const std::shared_ptr<KdModelData>& model)override;
	void SetPos(const Math::Vector3& pos)override;

	void SetTarget(std::shared_ptr<KdGameObject> _target);

private:

	Math::Vector3		m_pos;
	Math::Vector3		m_iniPos;
	Math::Vector3		m_rimPos;
	Math::Vector3		m_move;
	
	Math::Matrix		m_mRotaion;
	Math::Vector3		m_rot;

	int					m_moveLevel=0;

	std::shared_ptr<KdGameObject>			m_target = nullptr;

};
