#pragma once

class CameraBase;


#define TEN	10
#define CRITICAL_RANGE	5
#define FUMBLE_RANGE	96

#define	TEXTUREPASS "Asset/Textures/GameObject/CutIn/"
#define SOUNDPASS	"Asset/Sounds/SE/"

#define DRAW_TIME  120

class DiceManager:public KdGameObject
{
public:

	void Update()override;
	void DrawUnLit()override;
	const bool Dice(const int _judgeNum);

	void Ready(const Math::Matrix& _mat);

	void SetCamera(const std::shared_ptr<CameraBase>& _spCamera) { m_wpCamera = _spCamera; }

	void DrawSprite()override;

	
private:
	void Init()override;


	void Release();

	KdRandomGenerator m_randGen;

	std::weak_ptr<CameraBase> m_wpCamera;

	std::shared_ptr<KdModelData> m_spBlueD = nullptr;
	std::shared_ptr<KdModelData> m_spRedD = nullptr;

	std::shared_ptr<KdTexture> m_tex = nullptr;

	Math::Matrix m_mRedD = Math::Matrix::Identity;
	Math::Matrix m_mBlueD = Math::Matrix::Identity;

	float	m_drawTime = 0;


public:

	static DiceManager& GetInstance()
	{
		static DiceManager instance;

		return instance;
	}


private:
	DiceManager() { Init(); }
	~DiceManager()override { Release(); }

};
