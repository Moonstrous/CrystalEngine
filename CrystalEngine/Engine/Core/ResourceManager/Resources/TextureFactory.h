#pragma once
#include "Engine/Core/ResourceManager/Factory.h"
#include "TextureResource.h"

#include <unordered_map>

namespace Crystal {
	namespace Core {
		class TextureFactory : public IFactory
		{
		private:
			std::unordered_map<std::string, TextureResource*>* m_pResources;
		public:
			Resource* LoadResource(const std::string& resourceName) override;
			bool ReloadResource(const std::string& resourceName) override;
		};
	}
}