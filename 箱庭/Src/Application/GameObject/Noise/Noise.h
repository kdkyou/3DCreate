#pragma once

class Noise :public KdGameObject
{
public:
	Noise(){}
	~Noise(){}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void DrawUnLit()override;
	void DrawLit()override;
	void DrawSprite()override;

	void SetTexture(const std::shared_ptr<KdTexture>& _tex);

private:

	Math::Vector3		m_pos:

	std::shared_ptr<KdTexture> m_tex;
	std::shared_ptr<KdSquarePolygon> m_noisePoly;

	int							 m_drawLength = 0;

};