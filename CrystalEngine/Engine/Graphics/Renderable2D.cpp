#pragma once
#include "Renderable2D.h"

namespace Crystal {
	namespace Graphics {

		Renderable2D::Renderable2D(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
			: m_Position(position), m_Size(size), m_Color(color)
		{
			updateVertices();
		}

		Renderable2D& Renderable2D::SetPosition(const glm::vec2& newPos)
		{
			m_Position = newPos;
			updateVertices();
			return *this;
		}

		Renderable2D& Renderable2D::SetSize(const glm::vec2& newSize)
		{
			m_Size = newSize;
			updateVertices();
			return *this;
		}

		Renderable2D& Renderable2D::SetColor(glm::vec4 val)
		{
			m_Color = val;
			updateVertices();
			return *this;
		}

		Renderable2D& Renderable2D::Translate(const glm::vec2& deltaPos)
		{
			m_Position += deltaPos;
			updateVertices();
			return *this;
		}

		Renderable2D& Renderable2D::Scale(const glm::vec2& multiplier)
		{
			m_Size *= multiplier;
			updateVertices();
			return *this;
		}

		void Renderable2D::updateVertices()
		{
			m_pVertices = new Vertex[4]{
				Vertex{{m_Position.x			,m_Position.y			,0}		,m_Color},
				Vertex{{m_Position.x + m_Size.x	,m_Position.y			,0}		,m_Color},
				Vertex{{m_Position.x + m_Size.x	,m_Position.y + m_Size.y,0}		,m_Color},
				Vertex{{m_Position.x			,m_Position.y + m_Size.y,0}		,m_Color}
			};
		}

	}
}