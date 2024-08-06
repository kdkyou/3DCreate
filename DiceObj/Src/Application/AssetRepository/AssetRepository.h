#pragma once

class AssetRepository
{
public:

	std::shared_ptr<KdModelData> GetModel(std::string _modelName);

private:

	AssetRepository() { Init(); }

	void Init();

	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_modelMap;



public:

	static AssetRepository& Instance()
	{
		static AssetRepository instance;
		return instance;
	}
	
};