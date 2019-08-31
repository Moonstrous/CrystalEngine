#include "Buffer.h"

namespace Crystal {
	namespace Graphics {
		namespace GL {

			Buffer::Buffer()
			{
				glGenBuffers(1, &m_VboID);
			}

			Buffer::Buffer(const std::vector<float>& data,GLubyte componentCount)
			{
				glGenBuffers(1, &m_VboID);
				SetData(data,componentCount);
			}

			Buffer::Buffer(const std::initializer_list<float>& data, GLubyte componentCount)
			{
				glGenBuffers(1, &m_VboID);
				SetData(data,componentCount);
			}

			Buffer::Buffer(GLfloat* data, size_t count, GLubyte componentCount)
			{
				glGenBuffers(1, &m_VboID);
				SetData(data, count, componentCount);
			}

			Buffer& Buffer::SetData(const std::vector<float>& data,GLubyte componentCount)
			{
				m_ComponentCount = componentCount;
				Bind();
				glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &(data[0]), GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			Buffer& Buffer::SetData(const std::initializer_list<float>& data, GLubyte componentCount)
			{
				m_ComponentCount = componentCount;
				Bind();
				glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &(std::vector<float>(data)[0]), GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			Buffer& Buffer::SetData(GLfloat* data, size_t count, GLubyte componentCount)
			{
				m_ComponentCount = componentCount;
				Bind();
				glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			Buffer& Buffer::Bind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
				return *this;
			}

			Buffer& Buffer::Unbind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				return *this;
			}

			Buffer::~Buffer()
			{
				glDeleteBuffers(1, &m_VboID);
			}
		}
	}
}