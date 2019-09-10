#pragma once
#include "Resource.h"
#include <unordered_map>
#include <string>
// #StringView Consider StringView instead of const str ref
namespace Crystal {
	namespace Core {
		class Resource;
		class IFactory;
		using ResourceDatabase = std::unordered_map<std::string, std::shared_ptr<Resource>>;
		using FactoryMap = std::unordered_map<std::string, std::unique_ptr<IFactory>>;
		class ResourceManager
		{
		private:
			FactoryMap* m_pFactories;
			ResourceDatabase* m_pResourceDatabase;
			std::string m_DatabasePath;
		public:
			ResourceManager& RegisterResourceType(const std::string& resourceType, std::unique_ptr<IFactory> factory);
			ResourceManager& SetResourceDatabase(const std::string& databasePath);
			ResourceDatabase& GetResourceDatabase();
			Resource LoadResource(const std::string& resourceName);
			//int TypeStringToInt(const std::string& typeStr);
			std::unique_ptr<IFactory>& GetFactory(const std::string& resourceType);
		};
	}
}