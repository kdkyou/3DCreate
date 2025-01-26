#pragma once

class LaserSystem;

class LaserManager {

public:

	bool ChangeStage();



private:

	enum Level
	{
		One,
		Two,
		Three,
		Four,
	};

private:

	LaserManager() {}
	~LaserManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static LaserManager& Instance()
	{
		static LaserManager instance;
		return instance;
	}


};

#define FILEPATH "Asset/Data/GameObject/Pazzle/Laser/Stage"