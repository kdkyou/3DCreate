#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class Relief:public BaseGimmick
{
public:
	Relief(){}
	~Relief()override{}

	void SetModel(const std::shared_ptr<KdModelData>& model)override;

	void Update()override;

	void OnHit()override;
	void OnEncount()override;

	void DrawSprite()override;

	
private:

	std::shared_ptr<KdTexture>		m_fTexture		= nullptr;
	std::shared_ptr<KdTexture>      m_cthlhuTex = nullptr;
	bool							m_drawFkeyFlg	= false;
	bool							m_createFlg		= false;
};

#define RELIEFPATH "Asset/Textures/GameObject/Relief/"