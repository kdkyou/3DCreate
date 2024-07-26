#pragma once

class TPSCamera;

class DiceBase : public KdGameObject
{
public:
	DiceBase(){}
	~DiceBase()override{}

	void Init()override{}
	void Update()override{}
	void PostUpdate()override{}
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

	virtual void Shake(const int _number){}
	
protected:

	void Release();

	std::weak_ptr<KdModelWork> m_wpModelWork;
	std::weak_ptr<KdModelData> m_wpModel;
	
	std::shared_ptr<KdAnimator> m_spAnimetor;

	std::weak_ptr<TPSCamera> m_wpCamera;

	Math::Vector3			   m_pos;
	Math::Vector3			   m_moveDir;
	Math::Vector3			   m_rotDir;
	Math::Vector3			   m_DecidedRot;

};
