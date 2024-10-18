#pragma once

class BaseScene;

class SceneManager
{
public :

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType nextScene)
	{
		m_nextSceneType = nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();

	//マップシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetMapObjList();
	
	//ギミックシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetGimmickObjList();

	const int& GetReliefCount();
	void AddReliefCount();

	
	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj);
	void AddGimmick(const std::shared_ptr<KdGameObject>& obj);
	void AddNoise(const std::shared_ptr<KdGameObject>& obj);

	//imgui関連
	void Imgui();


	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		//レンダーターゲット初期化
		m_rtPack.CreateRenderTarget(1280, 720, true);
		//エフェクシア初期化
		KdEffekseerManager::GetInstance().Create(1280, 720);

		AssetLoad();

		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);

	}

	//レンダーターゲット切り替え関連
	void ChangeRenderTarget();
	//元に戻す関数
	void UndoRenderTarget();
	//出来上がったテクスチャを取得
	const std::shared_ptr<KdTexture>& GetRenderTargetTexture() const
	{
		return m_rtPack.m_RTTexture;
	}
	//void ChangeRenderStage();

	const int GetLength()const { return length; }

private :

	void AssetLoad();

	struct MapObject
	{
		std::string m_name;						//モデル名
		std::string m_conrtollName;				//操作時名
		std::shared_ptr<KdGameObject> m_obj;	
	};


	void AddMapObject(const std::shared_ptr<KdGameObject>& obj);

	//imgui関連
	enum class ObjectName
	{
		CathedralArch,
		CathedralNormal,
		CathedralRod,
		CathedralSentral,
		CathedralWall,
		Bridge,
		FenceNormal,
		FenceOneBreak,
		FenceBreaked,
		Pillar,
		Relief,
		Stairs,
		Tail,
		Temple,
		Box,
		SepBox,
		CorBox,
		WallBox,
		UpperBox,
		BreakWall,
		Cal,
	};

	enum class GimmickName
	{
		ArrowBox,
		BreakWall,
		FallPillar,
		Nidle,
		PitFall,
		RotateBridge,
		SlideDoor,
		Wall,
	};

	void CreateObject();
	void CreateMapObject(ObjectName name);
	void CreateGimmick();

	void Controll();

	void SaveMap();
	void LoadMap();
	void ClearMap();
	void SaveGimmick();
	void LoadGimmick();

	void List();
	//
	Math::Vector3	m_pos;
	bool m_settingFlg = false;
	Math::Vector3	m_scale;
	Math::Vector3	m_ang;
	// オブジェクトポインタ
	std::shared_ptr<KdGameObject> m_spNow = nullptr;
	int num = 0;
	std::list<std::shared_ptr<MapObject>> m_mapList;
	std::list<std::shared_ptr<MapObject>> m_gimmickList;

	int length = 1;

	
	// シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	//マップオブジェクトを入れたシーン
	std::shared_ptr<BaseScene> m_mapScene	  = nullptr;
	//ギミックオブジェクトを入れたシーン
	std::shared_ptr<BaseScene> m_gimmickScene = nullptr;

	std::shared_ptr<BaseScene> m_noiseScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Title;
	
	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	//レンダーターゲット切り替え
	KdRenderTargetPack	m_rtPack;
	KdRenderTargetChanger m_rtChanger;

private:

	SceneManager() {}
	~SceneManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};
