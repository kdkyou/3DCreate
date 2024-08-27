#pragma once

class Terrain : public KdGameObject
{
public:
	Terrain() {}
	virtual ~Terrain()		override {}

	void Update()			override;
	void DrawLit()			override;

	void SetModel(std::shared_ptr<KdModelData>& model);

	void OnHit()override;

private:

	void Release();
	
	std::shared_ptr<KdModelData> m_spModel = nullptr;

	bool						 m_drawFlg = false;

};