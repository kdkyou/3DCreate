#pragma once

class Character;

class Gate :public KdGameObject
{
public:
	Gate(){}
	~Gate(){}

	void Init()override;
	
	void Update()override;

	void DrawUnLit()override;

	void SetTarget(const std::shared_ptr<Character>& _target);

	void OnHit()override;

private:

	std::shared_ptr<KdSquarePolygon>  m_polygon = nullptr;

	std::shared_ptr<Character>	m_target = nullptr;


};