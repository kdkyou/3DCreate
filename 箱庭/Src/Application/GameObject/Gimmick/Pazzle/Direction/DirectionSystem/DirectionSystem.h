#pragma once

#include"../../../GimmickBase/GimmickBase.h"

class DirectionObject;

class DirectionSystem : public GimmickBase
{
public:

	void Init()override;

	void Update()override;
	
	void OnHit()override;

private:

	std::list<std::weak_ptr<DirectionObject>> m_objects;	//管理するオブジェクトのリスト

};