#pragma once

#define SHOW_TIME 180
#define SHOW_SHORT 60

class Information :public KdGameObject
{
public:
	Information(){}
	~Information()override{}

	void SetTexture(const std::string& path, bool longOrshort = false);

	void Update()override;
	void DrawSprite()override;

private:

	std::shared_ptr<KdTexture>		m_tex;

	int								m_showTime = 0;

};