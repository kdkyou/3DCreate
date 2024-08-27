#pragma once

#define HALF			0.5
#define RFTWO			0.2 
#define RFONE			0.1 
#define MOVE_DECREASE	0.0002
#define ONE_AROUND		360

class CameraBase;

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
	
	void SetModel(const std::shared_ptr<KdModelData> _spModel)
	{
		m_wpModel = _spModel;
	}

	void SetCamera(const std::shared_ptr<CameraBase> _camera)
	{
		m_wpCamera = _camera;
	}

	virtual void Shake(const int _number,const Math::Vector3 _pos, const Math::Vector3 _moveDir,const float _speed,const Math::Vector3 _rotDir){}
	
protected:

	void Release();

	std::weak_ptr<KdModelData>	m_wpModel;
	
	std::weak_ptr<CameraBase>	m_wpCamera;

	//座標
	Math::Vector3				m_pos;
	
	//移動方向
	Math::Vector3				m_moveDir;
	float						m_moveSpeed;
	
	//回転量
	Math::Vector3				m_rotDir;
	Math::Vector3				m_rot;
	
	//数字表記用
	Math::Vector3				m_DecidedRot;

	//行列関係
	Math::Matrix				m_mRotMat;
	Math::Matrix				m_mScaleMat;
	Math::Matrix				m_mTransMat;

	//残存時間
	int							m_showFrame;
};
