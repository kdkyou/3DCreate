#pragma once

#define CENTER 0

class Noise :public KdGameObject
{
public:
	Noise(){}
	~Noise(){}

	void Init()override;
	void Update()override;
//	void PostUpdate()override;

	void PreDraw()override;
	void DrawUnLit()override;
	void DrawLit()override;
	void DrawSprite()override;

	void SetTexture(const std::shared_ptr<KdTexture>& _tex, int _aliveTime = 60);

private:

	void Render();

	Math::Vector2	 m_pos;
	int m_ang = 0;
	float	m_waveLength =0.0f;

	std::shared_ptr<KdTexture> m_renderTex = nullptr;
	std::shared_ptr<KdTexture> m_apotheosisTex = nullptr;
	std::shared_ptr<KdTexture> m_totalTex = nullptr;
	std::shared_ptr<KdSquarePolygon> m_noisePoly = nullptr;

	int							 m_drawLength = 0;

	int							m_aliveTime;

	KdRandomGenerator		gene;

};