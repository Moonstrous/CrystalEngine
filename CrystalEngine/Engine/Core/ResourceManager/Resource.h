#pragma once
#include <string>
#include <vendor/nlohmann/json.hpp>

namespace Crystal {
	namespace Core {

		class Resource
		{
		private:
			std::string m_ResourceType;
			std::string m_ResourcePath;
			std::string m_ResourceName;
			std::string m_MetaData;
			int m_RefCout;
		public:
			const std::string& GetResourceName() const { return m_ResourceName; }
			const std::string& GetResourcePath() const { return m_ResourcePath; }
			const std::string& GetResourceType() const { return m_ResourceType; }
			const std::string GetResourceMetaData() const { return m_MetaData; }
			Resource& SetResourceName(const std::string& resourceName) { m_ResourceName = resourceName; return *this; }
			Resource& SetResourcePath(const std::string& resourcePath) { m_ResourcePath = resourcePath; return *this; }
			Resource& SetResourceType(const std::string& resourceType) { m_ResourceType = resourceType; return *this; }
			Resource& SetResourceMetaData(const std::string& resourceMetaData) { m_MetaData = resourceMetaData; return *this; }
		};

		using json = nlohmann::json;
		void to_json(json& j, const Resource& r)
		{
			j = json{ {"Name", r.GetResourceName()}, {"Path", r.GetResourcePath()}, {"Type", r.GetResourceType()} };
		}

		void from_json(const json& j, Resource& r) 
		{
			r.SetResourceName(j.at("Name"))
				.SetResourcePath(j.at("Path"))
				.SetResourceType(j.at("Type"))
				.SetResourceMetaData(j.at("MetaData"));
		}


	}
}