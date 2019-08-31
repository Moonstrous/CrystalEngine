#include "IndexBuffer.h"

namespace Crystal {
	namespace Graphics {
		namespace GL {

			IndexBuffer::IndexBuffer()
			{
				glGenBuffers(1, &m_IboID);
			}

			IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data)
			{
				glGenBuffers(1, &m_IboID);
				SetData(data);
			}

			IndexBuffer::IndexBuffer(const std::initializer_list<unsigned int>& data)
			{
				glGenBuffers(1, &m_IboID);
				SetData(data);
			}

			IndexBuffer::IndexBuffer(GLuint* data, size_t count )
			{
				glGenBuffers(1, &m_IboID);
				SetData(data, count);
			}

			IndexBuffer& IndexBuffer::SetData(const std::vector<unsigned int>& data)
			{
				m_Count = data.size();
				Bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &(data[0]), GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			IndexBuffer& IndexBuffer::SetData(const std::initializer_list<unsigned int>& data)
			{
				m_Count = data.size();
				Bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &(std::vector<unsigned int>(data)[0]), GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			IndexBuffer& IndexBuffer::SetData(GLuint* data, size_t count)
			{
				m_Count = count;
				Bind();
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
				Unbind();
				return *this;
			}

			IndexBuffer& IndexBuffer::Bind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboID);
				return *this;
			}

			IndexBuffer& IndexBuffer::Unbind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				return *this;
			}

			IndexBuffer::~IndexBuffer()
			{
				glDeleteBuffers(1, &m_IboID);
			}
		}
	}
}