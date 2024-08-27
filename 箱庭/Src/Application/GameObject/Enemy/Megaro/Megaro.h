#pragma once

#include"../../Gimmick/BaseGimmick/BaseGimmick.h"

#define MOVE_FRAME 600

class Character;

class Megaro:public BaseGimmick
{
public:
	Megaro(){}
	~Megaro()override{}

	void Update()override;

	void SetModel(std::shared_ptr<KdModelData>& model);
	void SetPos(const Math::Vector3& pos)override;

	void SetTarget(std::shared_ptr<KdGameObject> _target);

private:

	Math::Vector3		m_pos;
	Math::Vector3		m_iniPos;
	Math::Vector3		m_rimPos;
	Math::Vector3		m_move;
	
	Math::Matrix		m_mRotaion;
	Math::Vector3		m_rot;

	std::shared_ptr<KdGameObject>			m_target;

};
