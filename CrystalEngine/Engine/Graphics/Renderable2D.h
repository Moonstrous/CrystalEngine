#pragma once
#include "OpenGL/Shader.h"
#include "OpenGL/Buffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"

#include "Vertex.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace Crystal {
	namespace Graphics {

		const static unsigned int VERTEX_SIZE		= sizeof(Vertex);
		const static unsigned int MAX_BATCH			= 10000;
		const static unsigned int RENDERABLE_SIZE	= VERTEX_SIZE * 4;
		const static unsigned int MAX_BUFFER_SIZE	= MAX_BATCH * RENDERABLE_SIZE;
		const static unsigned int MAX_INDICES_SIZE	= MAX_BATCH * 6;

		class Renderable2D
		{
		private:
			glm::vec2 m_Position;
			glm::vec2 m_Size;
			glm::vec4 m_Color;
			Vertex* m_pVertices; // Array
		public:
			Renderable2D(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

			/* Getters */
			const glm::vec2& GetPosition() const { return m_Position; }
			const glm::vec2& GetSize() const { return m_Size; }
			Vertex* GetVertices() { return m_pVertices; }

		};

	}
}