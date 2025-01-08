#pragma once

#include"../PuzzleObject.h"

class LaserObject :public PuzzleObject
{
public:
	LaserObject(){}
	~LaserObject()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawUnLit()override;


protected:

	std::shared_ptr<KdTrailPolygon>	m_spTrail = nullptr;

	bool m_isShot = false;

	Math::Matrix m_mNpMat;
};
