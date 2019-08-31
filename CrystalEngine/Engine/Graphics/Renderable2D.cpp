#pragma once
#include "Renderable2D.h"

namespace Crystal {
	namespace Graphics {

		Renderable2D::Renderable2D(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
			: m_Position(position), m_Size(size), m_Color(color)
		{
			m_pVertices = new Vertex[4]{
				Vertex{{position.x		 ,position.y		 ,0}	,color},
				Vertex{{position.x + size.x,position.y		 ,0}	,color},
				Vertex{{position.x + size.x,position.x + size.y,0}	,color},
				Vertex{{position.x		 ,position.y + size.y,0}	,color}
			};
		}

	}
}