#include "VertexArray.h"

namespace Crystal {
	namespace Graphics {
		namespace GL {



			VertexArray::VertexArray()
			{
				glGenVertexArrays(1, &m_VertArrayID);
			}

			VertexArray::~VertexArray()
			{
				for (Buffer* pBuffer : m_Buffers)
					delete pBuffer;
			}

			VertexArray& VertexArray::AddBuffer(Buffer* buffer,GLuint index)
			{
				Bind();
				buffer->Bind();
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
				buffer->Unbind();
				Unbind();
				m_Buffers.push_back(buffer);
				return *this;
			}

			VertexArray& VertexArray::Bind()
			{
				glBindVertexArray(m_VertArrayID);
				for (Buffer* pBuffer : m_Buffers)
				{
					pBuffer->Bind();
				}
				return *this;
			}

			VertexArray& VertexArray::Unbind()
			{
				for (Buffer* pBuffer : m_Buffers)
				{
					pBuffer->Unbind();
				}
				glBindVertexArray(0);
				return *this;
			}

		}
	}
}