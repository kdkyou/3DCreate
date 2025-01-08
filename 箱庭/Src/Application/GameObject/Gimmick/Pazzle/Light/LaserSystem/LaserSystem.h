#pragma once

#include"../../../GimmickBase/GimmickBase.h"

class LaserObject;

class LaserSystem : public GimmickBase
{
public:

	//ギミックの状態が更新された時に呼び出されるコールバック関数を設定
	void SetCallback(std::function<void()>callback) {
		m_callback = callback;
	}

	bool SetParam(const std::string& fileName);
	//オブジェクトを追加
	void AddObject(const std::weak_ptr<LaserObject>& object)
	{
		m_objects.push_back(object);
	}
	

	//全てのオブジェクトの状態を確認
	void CheckAlignment();


private:

	//オブジェクト破壊時にコールバック関数を呼び出す
	void BreakCallBack();


	std::vector<std::weak_ptr<LaserObject>> m_objects;		//管理するオブジェクトのリスト
	std::function<void()> m_callback = nullptr;				//状態変化時のコールバック

};