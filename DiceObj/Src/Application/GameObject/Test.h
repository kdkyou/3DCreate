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

	void OnHit()		override;

private:

	void Release();

	std::shared_ptr<KdModelData> m_model;

	Math::Color			color;

	Math::Vector3		extents;
};