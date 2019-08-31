#pragma once
#include "vendor/glad/glad.h"
#include "Buffer.h"

#include <vector>

namespace Crystal {
	namespace Graphics {
		namespace GL {

			class VertexArray
			{
			private:
				GLuint m_VertArrayID;
				std::vector<Buffer*> m_Buffers;
			public:
				VertexArray();
				~VertexArray();

				VertexArray& AddBuffer(Buffer* buffer,GLuint index);
				VertexArray& Bind();
				VertexArray& Unbind();

			};

		}
	}
}