#pragma once
#include "vendor/glad/glad.h"
#include <vector>
#include <initializer_list>


namespace Crystal {
	namespace Graphics {
		namespace GL {
		
			class Buffer
			{
			private:
				GLuint m_VboID;
				GLubyte m_ComponentCount;
			public:
				Buffer();
				Buffer(const std::vector<float>& data, GLubyte componentCount);
				Buffer(const std::initializer_list<float>& data, GLubyte componentCount);
				Buffer(GLfloat* data, size_t count, GLubyte componentCount);

				Buffer& SetData(const std::vector<float>& data, GLubyte componentCount);
				Buffer& SetData(const std::initializer_list<float>& data, GLubyte componentCount);
				Buffer& SetData(GLfloat* data, size_t count, GLubyte componentCount);

				Buffer& Bind();
				Buffer& Unbind();

				inline GLubyte GetComponentCount() const { return m_ComponentCount; }

				~Buffer();
			};

		}
	}
}