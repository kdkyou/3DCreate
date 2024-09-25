#pragma once

#define	SIXTY	60;

class Cutin:public KdGameObject
{
public:
	Cutin(){}
	~Cutin() override {}

	void Set(const std::string& _texPass, const std::string& _soundPass);
	void Update()override;
	void DrawSprite()override;

private:

	std::shared_ptr<KdTexture>		m_tex = nullptr;

	//表示時間
	int								m_time = 0 ;

};
