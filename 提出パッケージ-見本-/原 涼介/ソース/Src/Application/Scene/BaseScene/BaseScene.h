#pragma once

class Character;

class BaseScene
{
public :

	BaseScene() { Init(); }
	virtual ~BaseScene() {}

	virtual void PreUpdate();
	virtual void Update();
	virtual void PostUpdate();

	virtual void PreDraw();
	virtual void Draw();
	virtual void DrawSprite();
	virtual void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& obj)
	{
		m_objList.push_back(obj);
	}

	//カウント増やす
	void IncreaseCount() { m_count++; }
	const int GetCount() { return m_count; }

	void SetChara(std::shared_ptr<Character> chara);


protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();
	virtual void Init();

	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;

	int										 m_count;
};
