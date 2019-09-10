#include "ResourceManager.h"
#include "vendor/nlohmann/json.hpp"
#include "Factory.h"
#include <fstream>


namespace Crystal {
	namespace Core {
		ResourceManager& ResourceManager::RegisterResourceType(const std::string& resourceType, std::unique_ptr<IFactory> factory)
		{
			m_pFactories->emplace(resourceType, factory);
			return *this;
		}
		ResourceManager& ResourceManager::SetResourceDatabase(const std::string& databasePath)
		{
			using json = nlohmann::json;
			
			m_DatabasePath = databasePath;
			std::ifstream ifs(databasePath);
			if(ifs.fail())
			{
				exit(0);
			}
			json dbJson;
			ifs >> dbJson;
			ifs.close();
			return *this;
		}
		Resource ResourceManager::LoadResource(const std::string& resourceName)
		{
			return m_pFactories->at(m_pResourceDatabase->at(resourceName)->GetResourceType())->LoadResource(resourceName);
		}
	}
}

