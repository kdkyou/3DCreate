#pragma once

#include"../BaseScene/BaseScene.h"

class CameraBase;

class GameScene : public BaseScene
{
public :

	GameScene()		{ Init(); }
	~GameScene()	{}

	bool SetCameraTarget(std::weak_ptr<KdGameObject> target);

private:

	//使用しているカメラ
	std::weak_ptr<CameraBase> m_wpCamera;

	//カメラのターゲットになっているオブジェクトの名前
	std::string m_strCameraTarget = "Gate";

	std::shared_ptr<KdTexture> m_tex = nullptr;

	//カメラのターゲットの変更
	void ChangeCameraTarget();

	//指定した名前で検索して合致したオブジェクトを返す
	std::shared_ptr<KdGameObject> FindObjectWithName(const std::string& name);

	void Event() override;
	void Init() override;

	int time;
	
};
