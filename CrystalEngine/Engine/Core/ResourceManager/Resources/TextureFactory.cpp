#include "TextureFactory.h"
#include "Engine/Core/ResourceManager/ResourceManager.h"

#include "vendor/nlohmann/json.hpp"

using json = nlohmann::json;

namespace Crystal {
	namespace Core {
		Resource* TextureFactory::LoadResource(const std::string& resourceName)
		{
			using Tex = Graphics::GL::Texture;
			TextureResource* resource = (TextureResource*)m_pResourceManager->GetResourceDatabase().at(resourceName);
			json resourceMD = resource->GetResourceMetaData();
			Tex::Filter filter = {resourceMD.value("Filters/Mag"_json_pointer, Tex::Filter::Linear), resourceMD.value("Filters/Min"_json_pointer, Tex::Filter::Linear)};
			Tex::Wrap wrap = { resourceMD.value("Wrapping/S",),resourceMD.value("Wrapping/T",) };
			resource->pTexture->SetData(resource->GetResourcePath(),wrap,filter);

		}

		bool TextureFactory::ReloadResource(const std::string& resourceName)
		{

		}

	}
}

