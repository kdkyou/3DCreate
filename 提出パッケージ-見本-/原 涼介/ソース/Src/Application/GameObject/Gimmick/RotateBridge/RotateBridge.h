#pragma once
#include"../BaseGimmick/BaseGimmick.h"

#define ROTATE_ONCE_RIMIT 90
#define STOP_FRAME		120
#define ADD_ANGLE 1

class RotateBridge :public GimmickBase
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

	bool IsRideable()const  override { return true; }

private:


	Math::Matrix m_mGear =Math::Matrix::Identity;

	int m_ang = 0;				//角度
	int m_spin = 0;				//90度分までの回転量計測
	int m_stopFrame = 0;		//停止時間
	bool m_rotFlg = false;		//稼働フラグ
};
