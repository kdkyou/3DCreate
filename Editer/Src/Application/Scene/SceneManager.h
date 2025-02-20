﻿#pragma once

class BaseScene;

struct MapObject
{
	std::string m_name;
	std::shared_ptr<KdGameObject> m_obj;
};

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

	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj);

	void Imgui();

private :

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
		Megaro,
		Cal,
	};
	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	// シーン切り替え関数
	void ChangeScene(SceneType sceneType);

	//imgui関連
	void CreateObject(ObjectName name);
	void CreateGimmick();
	void SaveMap();
	void LoadMap();
	void ClearMap();
	void SaveGimic();
	void LoadGimmick();
	//
	Math::Vector3	m_pos;
	Math::Vector3	m_scale;
	Math::Vector3	m_rot;
	std::list<std::shared_ptr<MapObject>> m_mapList;
	std::list<std::shared_ptr<MapObject>> m_gimmickList;
	// オブジェクトポインタ
	std::shared_ptr<KdGameObject> m_spNow	 = nullptr;
	int num=0;


	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Title;
	
	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;


	

private:

	SceneManager() { Init(); }
	~SceneManager() { //SaveGimic(); SaveMap();
	}

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
