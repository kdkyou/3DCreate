#pragma once

class Cal : public KdGameObject
{
public:
	Cal() {}
	virtual ~Cal()		override {}

	void DrawUnLit()			override;

	void SetModel(std::shared_ptr<KdModelData>& model);

	
private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	
};