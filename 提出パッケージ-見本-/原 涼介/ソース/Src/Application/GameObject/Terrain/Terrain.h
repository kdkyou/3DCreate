#pragma once

#define WATER_SPEED 0.00002f

class Terrain : public KdGameObject
{
public:
	Terrain() {}
	virtual ~Terrain()		override {}

	void Update()			override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()			override;

	void SetModel(std::shared_ptr<KdModelData>& model);

	void OnHit()override;

private:

	void Release();
	
	std::shared_ptr<KdModelData> m_spModel = nullptr;

//	std::shared_ptr<KdTexture>  m_spnormalTex = nullptr;

	bool						 m_drawFlg = false;

	
};