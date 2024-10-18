#pragma once

class AssetRepository
{
public:

	std::shared_ptr<KdModelData> GetModel(std::string _modelName);
	std::list<std::string> GetSoundList(){ return m_soundList; }

private:

	AssetRepository() { Init(); }

	void Init();

	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_modelMap;

	std::list<std::string> m_soundList;


public:

	static AssetRepository& Instance()
	{
		static AssetRepository instance;
		return instance;
	}
	
};