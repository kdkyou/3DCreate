#pragma once

#define HALF 0.5
#define RFTWO 0.2 
#define RFONE 0.1 
#define RFZFIVE 0.05
#define MOVE_DECREASE 0.0002

class TPSCamera;

class DiceBase : public KdGameObject
{
public:
	DiceBase(){}
	~DiceBase()override{}

	void Init()override{}
	void Update()override;
	void PostUpdate()override;
	void DrawBright()override;
	void DrawUnLit()override;

	void SetModelWork(const std::shared_ptr<KdModelWork> _spModel)
	{
		m_wpModelWork = _spModel;
	}
	
	void SetModel(const std::shared_ptr<KdModelData> _spModel)
	{
		m_wpModel = _spModel;
	}

	void SetCamera(const std::shared_ptr<TPSCamera> _camera)
	{
		m_wpCamera = _camera;
	}

	virtual void Shake(const int _number,const Math::Vector3 _pos, const Math::Vector3 _moveDir,const float _speed,const Math::Vector3 _rotDir){}
	
protected:

	void Release();

	std::weak_ptr<KdModelWork> m_wpModelWork;
	std::weak_ptr<KdModelData> m_wpModel;
	
	std::shared_ptr<KdAnimator> m_spAnimetor;

	std::weak_ptr<TPSCamera> m_wpCamera;

	//座標
	Math::Vector3			   m_pos;
	
	//移動方向
	Math::Vector3			   m_moveDir;
	float					   m_moveSpeed;
	
	//回転量
	Math::Vector3			   m_rotDir;
	Math::Vector3			   m_rot;
	
	//数字表記用
	Math::Vector3			   m_DecidedRot;

	//行列関係
	Math::Matrix			   m_mRotMat;
	Math::Matrix			   m_mScaleMat;
	Math::Matrix			   m_mTransMat;

};
