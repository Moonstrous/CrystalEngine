#pragma once
#include "glad/glad.h"
#include <string>
#include "vendor/nlohmann/json.hpp"

namespace Crystal {
	namespace Graphics {
		namespace GL {
			class Texture {
			public:
				struct Wrap
				{
					// Come up with a better alternative utilizing c++17 (MagicEnum ... etc)
					// and Make use of C++17 Features !
					enum WrappingTypes
					{
						Repeat = GL_REPEAT,
						MirroredRepeat = GL_MIRRORED_REPEAT,
						ClampToEdge = GL_CLAMP_TO_EDGE,
						ClampToBorder = GL_CLAMP_TO_BORDER
					} S, T;
					NLOHMANN_JSON_SERIALIZE_ENUM(WrappingTypes, {
						{Repeat,"Repeat"},
						{MirroredRepeat,"MirroredRepeat"},
						{ClampToEdge,"ClampToEdge"},
						{ClampToBorder,"ClampToBorder"} })
				};
				struct Filter
				{
					enum Filters 
					{
						Nearest = GL_NEAREST,
						Linear = GL_LINEAR
					} Min, Mag;
					NLOHMANN_JSON_SERIALIZE_ENUM(Filters)
					
				};
			private:
				GLuint m_TextureID;
				int m_Width, m_Height, m_NrChannels;
			public:
				Texture();
				~Texture();

				Texture& Bind();
				Texture& Unbind();

				Texture& SetData(const std::string& texturePath,const Wrap& wrap,const Filter& filter);
				GLuint GetTextureID() { return m_TextureID; }
			};
		}
	}
}