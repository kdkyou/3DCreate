#pragma once
#include"../BaseGimmick/BaseGimmick.h"

class RotateBridge :public BaseGimmick
{
public:
	RotateBridge() {}
	~RotateBridge()override {}

	void SetModel(const std::shared_ptr<KdModelData>& model)override;
	void SetModel(const std::shared_ptr<KdModelWork>& model)override;
	
	void Init()override;
	void Update()override;
	
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	//void OnHit()override;

	bool IsRideable()const { return true; }

private:


	Math::Matrix m_mGear =Math::Matrix::Identity;

	int m_ang = 0;;
	int m_spin = 0;

};
