#pragma once

#include "vendor/glad/glad.h"
#include <vector>
#include <initializer_list>

namespace Crystal {
	namespace Graphics {
		namespace GL {

			class IndexBuffer
			{
			private:
				GLuint m_IboID;
				GLubyte m_Count;
			public:
				IndexBuffer();
				IndexBuffer(const std::vector<unsigned int>& data);
				IndexBuffer(const std::initializer_list<unsigned int>& data);
				IndexBuffer(GLuint* data, size_t count);
				
				IndexBuffer& SetData(const std::vector<unsigned int>& data);
				IndexBuffer& SetData(const std::initializer_list<unsigned int>& data);
				IndexBuffer& SetData(GLuint* data, size_t count);
				
				IndexBuffer& Bind();
				IndexBuffer& Unbind();

				inline GLubyte GetCount() const { return m_Count; }

				~IndexBuffer();
			};

		}
	}
}