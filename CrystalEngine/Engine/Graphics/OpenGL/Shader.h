#pragma once
#include <string>
#include <fstream>
#include "vendor/glad/glad.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"

namespace Crystal {
	namespace Graphics {
		namespace GL {
			class Shader {
				typedef GLuint ShaderID;
				typedef GLuint ShaderProgramID;
				typedef GLuint ShaderType;
			public:
			private:
				std::string m_ShaderName;
				std::string m_ShaderPath;
				ShaderID m_VertShaderID;
				ShaderID m_FragShaderID;
				ShaderProgramID m_ShaderProgramID;

				int m_AttribCount = 0;

				std::ifstream ifs;
			public:
				Shader(std::string shaderName, std::string shaderPath);
				const std::string& GetShaderName() { return m_ShaderName; }

				void Bind();
				void Unbind();

				GLint GetUniformLocation(const std::string& uniformName);
				Shader& SetUniform(const std::string& uniformName, const glm::mat4& value);
				Shader& AddAttribute(const std::string& attributeName);

			private:
				ShaderID createShader(ShaderType shaderType);
			};
		}
	}
}
