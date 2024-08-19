#pragma once

class Test :public KdGameObject
{
public:
	Test()			{}
	~Test()override {}

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void SetModel(std::shared_ptr<KdModelData>& model);

	void OnHit()		override;

private:

	void Release();

	std::shared_ptr<KdModelData> m_spModel;

	Math::Color			color;

	Math::Vector3		extents;
};