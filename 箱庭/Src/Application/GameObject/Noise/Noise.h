#pragma once

#define CENTER 0

class Noise :public KdGameObject
{
public:
	Noise(){}
	~Noise(){}

	void Update()override;

	void PreDraw()override;
	void DrawUnLit()override;
	void DrawLit()override;
	void DrawSprite()override;

	void SetParam(const std::shared_ptr<KdTexture>& _tex, int _aliveTime = 60,int _drawLength = 100,const Math::Color& _colr=kWhiteColor,bool _isPlay=true);

private:

	Math::Vector2	 m_pos;
	int m_ang = 0;
	float	m_waveLength =0.0f;

	Math::Color m_color =kWhiteColor;

	//BGMON
	bool    m_isPlayMusic = false;

	std::shared_ptr<KdTexture> m_renderTex = nullptr;
	std::shared_ptr<KdTexture> m_apotheosisTex = nullptr;
	std::shared_ptr<KdTexture> m_totalTex = nullptr;
	std::shared_ptr<KdSquarePolygon> m_noisePoly = nullptr;

	int							 m_drawLength = 0;

	int							m_aliveTime = 0;

	KdRandomGenerator		gene;

};