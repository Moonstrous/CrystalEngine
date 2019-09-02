#pragma once
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Crystal {
	namespace Graphics {
		struct Vertex
		{
			Vertex(const glm::vec3& position, const glm::vec4& color = { 1,1,1,1 })
				:position(position), color(color) {}
			Vertex() {}
			glm::vec3 position;
			glm::vec4 color;
		};
		enum VertexAttribs : unsigned int
		{
			Position,
			Color
		};
	}
}