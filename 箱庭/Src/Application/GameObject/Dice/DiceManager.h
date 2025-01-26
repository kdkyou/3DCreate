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
	void DrawBright()override;

	const bool Dice(const int _judgeNum);

	void CheckBlueKey() { m_keyType |= Bit::Blue; }
	void CheckRedKey() { m_keyType |= Bit::Red; }

	const bool ReadKey()const;
	
	void Ready(const Math::Matrix& _mat);

	void SetCamera(const std::shared_ptr<CameraBase>& _spCamera) { m_wpCamera = _spCamera; }

	
private:

	enum Bit
	{
		no,
		Blue = 1 << 0,
		Red = 1 << 1,
	};

	void Init()override;

	void Release();

	UINT m_keyType= Bit::no;

	KdRandomGenerator m_randGen;

	std::weak_ptr<CameraBase> m_wpCamera;

	std::shared_ptr<KdModelData> m_spBlueD = nullptr;
	std::shared_ptr<KdModelData> m_spRedD = nullptr;

	std::shared_ptr<KdTexture> m_tex = nullptr;

	Math::Matrix m_mRedD = Math::Matrix::Identity;
	Math::Matrix m_mRed = Math::Matrix::Identity;
	Math::Matrix m_mBlueD = Math::Matrix::Identity;
	Math::Matrix m_mBlue = Math::Matrix::Identity;

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
