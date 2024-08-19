#include "AssetRepository.h"
#include "json.hpp"

std::shared_ptr<KdModelData> AssetRepository::GetModel(std::string _modelName)
{
	auto it = m_modelMap.find(_modelName);
	if (it != m_modelMap.end()) 
	{
		return it->second;
	}
	return nullptr;
}

void AssetRepository::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/ModelRepository.json");
	inFile >> j;

	std::shared_ptr<KdModelData> model = nullptr;

	for(auto& item : j)
	{
		model = std::make_shared<KdModelData>();
		model->Load(item["Path"]);
		m_modelMap.insert({ item["Name"], model });
	}
}
