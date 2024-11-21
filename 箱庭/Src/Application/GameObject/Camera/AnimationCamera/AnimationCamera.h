#pragma once

class GameScene;

class AnimationCamera :public KdGameObject
{
public:
	AnimationCamera(){}
	~AnimationCamera(){}

	void Update()override;
	void Init()override;

	//情報のセット
	void SetAnimationInfo(
		const std::shared_ptr<KdGameObject>& start, 
		const std::shared_ptr<KdGameObject>& end, float spd = 0.01f);

private:


	//スタート地点とゴール地点のオブジェクト
	std::weak_ptr<KdGameObject> m_wpStart;
	std::weak_ptr<KdGameObject> m_wpEnd;

	//進行具合 (0～1)
	float m_progress = 0.0f;

	//進行スピード
	float m_speed = 0.01f;

};