#pragma once

class Texture :public KdGameObject
{
public:
	Texture() {}
	~Texture()override {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	void SetTexAlphaPos(const std::string& path, bool check = false,Math::Vector2 _pos={});

private:

	//画像
	std::shared_ptr<KdTexture>		m_tex;

	//位置
	Math::Vector2					m_pos;

	//アルファ値
	Math::Color						m_color;
	float							m_alpha = 0.f;
	float							m_addAlpha = 0.f;

	//アルファ値変更フラグ
	bool							m_checkAlpha=false;
};