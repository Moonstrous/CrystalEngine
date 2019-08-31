#pragma once
#include <deque>
#include "Renderable2D.h"
#include "OpenGL/VertexArray.h"

namespace Crystal {
	namespace Graphics {

		class Renderer2D
		{
		private:
			GLuint m_VertexBufferID;
			GLuint m_VertexArrayID;
			GL::IndexBuffer* m_IndexBuffer;
			unsigned int m_IndexCount;
			Vertex* m_pVertexBuffer;
			glm::mat4 m_Projection;


		public:
			Renderer2D(glm::mat4 projection);
			~Renderer2D();
			Renderer2D& Begin();
			Renderer2D& Push(Renderable2D* renderable);
			Renderer2D& End();
			Renderer2D& Flush();
		private:
			void init();
		};

	}
}