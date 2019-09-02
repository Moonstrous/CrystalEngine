#include "Renderer2D.h"

namespace Crystal {
	namespace Graphics {



		Renderer2D::Renderer2D(glm::mat4 projection)
			:m_Projection(projection), m_IndexCount(0)
		{
			init();
		}

		Renderer2D::~Renderer2D()
		{
			delete m_IndexBuffer;
			glDeleteBuffers(1, &m_VertexBufferID);
		}

		Renderer2D& Renderer2D::Begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
			m_pVertexBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			
			return *this;
		}

		Renderer2D& Renderer2D::Push(Renderable2D* renderable)
		{
			Vertex* vertices = renderable->GetVertices();
				*m_pVertexBuffer	= vertices[0];
			*(++m_pVertexBuffer)	= vertices[1];
			*(++m_pVertexBuffer)	= vertices[2];
			*(++m_pVertexBuffer)	= vertices[3];
			m_pVertexBuffer++;
			m_IndexCount += 6;
			return *this;
		}

		Renderer2D& Renderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return *this;
		}

		Renderer2D& Renderer2D::Flush()
		{
			glBindVertexArray(m_VertexArrayID);
			m_IndexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
			m_IndexBuffer->Unbind();
			glBindVertexArray(0);
			m_IndexCount = 0;
			return *this;
		}

		void Renderer2D::init()
		{
			glGenVertexArrays(1, &m_VertexArrayID);
			glGenBuffers(1, &m_VertexBufferID);
			
			glBindVertexArray(m_VertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(VertexAttribs::Position);
			glVertexAttribPointer(VertexAttribs::Position, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(VertexAttribs::Color);
			glVertexAttribPointer(VertexAttribs::Color,4,GL_FLOAT,GL_FALSE,VERTEX_SIZE,(const void*)offsetof(Vertex,color));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint indices[MAX_INDICES_SIZE];

			unsigned int offset = 0;
			for (int i = 0; i < MAX_INDICES_SIZE; i += 6)
			{
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IndexBuffer = new GL::IndexBuffer(indices, MAX_INDICES_SIZE);
			glBindVertexArray(0);

		}

	}
}