#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class Relief:public GimmickBase
{
public:
	Relief(){}
	~Relief()override{}

	void SetModel(const std::shared_ptr<KdModelData>& model)override;

	void Update()override;

	void OnHit()override;
	void OnEncount()override;

	void DrawSprite()override;

	void SetNum(int _num) { m_number = _num; }
	
private:

	int m_number = 0;

	std::shared_ptr<KdTexture>		m_fTexture		= nullptr;
	std::shared_ptr<KdTexture>      m_cthlhuTex = nullptr;
	bool							m_drawFkeyFlg	= false;
	bool							m_createFlg		= false;
	bool							m_isInfor = false;
};

#define RELIEFPATH "Asset/Textures/GameObject/Relief/"