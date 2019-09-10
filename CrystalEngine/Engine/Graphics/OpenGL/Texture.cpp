#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb/stb_image.h"
#include <iostream>

namespace Crystal {
	namespace Graphics {
		namespace GL {

			Texture& Texture::Bind()
			{
				glBindTexture(GL_TEXTURE_2D, m_TextureID);
			}
			Texture& Texture::Unbind()
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			Texture& Texture::SetData(const std::string& texturePath, const Wrap& wrap, const Filter& filter)
			{
				unsigned char* data = stbi_load("container.jpg", &m_Width, &m_Height, &m_NrChannels, 0);
				if (data) {
					glGenTextures(1, &m_TextureID);
					glBindTexture(GL_TEXTURE_2D, m_TextureID);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap.S);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap.T);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter.Min);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter.Mag);
					glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_Width,m_Height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
					glGenerateMipmap(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, 0);
					stbi_image_free(data);
				}
				else {
					std::cout << "FAILED to load texture from" << texturePath << '\n';
				}
				return *this;
			}

		}
	}
}

