#pragma once

#include"../BaseGimmick/BaseGimmick.h"

class Relief:public BaseGimmick
{
public:
	Relief(){}
	~Relief()override{}

	void SetModel(std::shared_ptr<KdModelData>& model);

	void Update()override;

	void OnHit()override;
	void OnEncount()override;

	void DrawSprite()override;

	
private:

	std::shared_ptr<KdTexture>		m_fTexture		= nullptr;
	bool							m_drawFkeyFlg	= false;
	bool							m_createFlg		= false;
};

#define RELIEFPATH "Asset/Textures/GameObject/Relief/"