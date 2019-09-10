#pragma once
#include "Engine/Core/ResourceManager/Resource.h"
#include "Engine/Graphics/OpenGL/Texture.h"

namespace Crystal {
	namespace Core {
		class TextureResource : public Resource
		{
		public:
			Graphics::GL::Texture* pTexture;
		};
	}
}