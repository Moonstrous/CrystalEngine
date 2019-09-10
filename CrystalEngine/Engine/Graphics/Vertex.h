#pragma once
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Crystal {
	namespace Graphics {
		struct Vertex
		{
			Vertex(const glm::vec3& position, const glm::vec4& color = { 1,1,1,1 }, const glm::vec3& textureCoords = { 0,0,0})
				:position(position), color(color) {}
			Vertex() {}
			glm::vec3 position;
			glm::vec4 color;
			glm::vec3 textureCoordinates;
		};
		enum VertexAttribs : unsigned int
		{
			Position,
			Color,
			TextureCoordinates
		};
	}
}
