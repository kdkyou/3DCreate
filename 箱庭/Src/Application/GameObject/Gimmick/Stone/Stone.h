#pragma once
#include"../GimmickBase/GimmickBase.h"

#define ALIVE_TIME 160;

class Stone :public GimmickBase
{
public:
	Stone() {}
	~Stone() {}

	void Init()override;
	void SetModel(const std::shared_ptr<KdModelData>& model);

	void Update()override;
	void PostUpdate()override;

	void DrawLit()override;
	void GenerateDepthMapFromLight()override;

	void SetParam(const Math::Matrix& _mat, const Math::Vector3& _dir, float _spd);

	void OnHit()override;

private:



	//座標
	Math::Vector3							m_pos = {};

	//移動方向
	Math::Vector3							m_moveDir = {};
	//移動量
	float									m_moveSpd = 0.f;

	//生存時間
	int										m_aliveTime = 0;

	//ディゾルブフラグ
	bool									m_dissolveFlg = false;
	float									m_dissolve = 0.0f;


	std::shared_ptr<KdTrailPolygon>			m_trail;

	
};

#define PATH "Asset/Textures/GameObject/Trail/Babul.png"