#pragma once

class CameraBase;


#define TEN	10
#define CRITICAL_RANGE	5
#define FUMBLE_RANGE	96

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/SE/"

class DiceManager:public KdGameObject
{
public:

	void Update()override;
	void DrawUnLit()override;
	const bool Dice(const int _judgeNum,const std::weak_ptr<CameraBase>& _wpCamera);

private:

	void Release();

	KdRandomGenerator m_randGen;

	std::shared_ptr<KdModelData> m_spBlueD = nullptr;
	std::shared_ptr<KdModelData> m_spRedD = nullptr;


public:

	static DiceManager& GetInstance()
	{
		static DiceManager instance;

		return instance;
	}


private:
	DiceManager() {}
	~DiceManager()override { Release(); }

};
