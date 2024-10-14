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
	void DrawSprite()override;

	void SetTexture(const std::shared_ptr<KdTexture>& _tex);

private:

	std::shared_ptr<KdTexture> m_tex;

};