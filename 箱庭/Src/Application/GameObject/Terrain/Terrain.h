#pragma once


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

	Math::Vector2 m_offset;


	bool						 m_drawFlg = false;

	
};