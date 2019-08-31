#pragma once
#include "Shader.h"
#include "SDL2/SDL_log.h"

#include <vector>

namespace Crystal {
	namespace Graphics {
		namespace GL {
			Shader::Shader(std::string shaderName, std::string shaderPath)
				:m_ShaderName(shaderName), m_ShaderPath(shaderPath)
			{
				m_VertShaderID = createShader(GL_VERTEX_SHADER);
				m_FragShaderID = createShader(GL_FRAGMENT_SHADER);

				m_ShaderProgramID = glCreateProgram();
				glAttachShader(m_ShaderProgramID, m_VertShaderID);
				glAttachShader(m_ShaderProgramID, m_FragShaderID);
				glLinkProgram(m_ShaderProgramID);

				GLint success = 0;
				glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);
				if (!success)
				{
					GLint maxLength = 0;
					glGetProgramiv(m_ShaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);

					// The maxLength includes the NULL character
					std::vector<char> errorLog(maxLength);
					glGetProgramInfoLog(m_ShaderProgramID, maxLength, &maxLength, &(errorLog[0]));

					SDL_Log("OGL : Program failed to link : \n %s", &(errorLog[0]));

					// We don't need the program anymore.
					glDeleteProgram(m_ShaderProgramID);
					// Don't leak shaders either.
					glDeleteShader(m_VertShaderID);
					glDeleteShader(m_FragShaderID);

					// Use the infoLog as you see fit.

					// In this simple program, we'll just leave
					return;
				}
				glDetachShader(m_ShaderProgramID, m_VertShaderID);
				glDetachShader(m_ShaderProgramID, m_FragShaderID);
				glDeleteShader(m_VertShaderID);
				glDeleteShader(m_FragShaderID);
			}

			void Shader::Bind()
			{
				glUseProgram(m_ShaderProgramID);
				for (int attr = 0; attr < m_AttribCount; ++attr)
				{
					glEnableVertexAttribArray(attr);
				}
			}

			void Shader::Unbind()
			{
				glUseProgram(0);
				for (int attr = 0; attr < m_AttribCount; ++attr)
				{
					glDisableVertexAttribArray(attr);
				}
			}

			GLint Shader::GetUniformLocation(const std::string& uniformName)
			{
				GLint location = glGetUniformLocation(m_ShaderProgramID, uniformName.c_str());
				if (location == GL_INVALID_INDEX)
				{
					SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Location of Uniform [%s] invalid", uniformName.c_str());
					exit(-1);
					return location;
				}
			}

			Shader& Shader::SetUniform(const std::string& uniformName, const glm::mat4& value)
			{
				glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
				return *this;
			}

			Shader& Shader::AddAttribute(const std::string& attributeName)
			{
				glBindAttribLocation(m_ShaderProgramID, m_AttribCount++, attributeName.c_str());
				return *this;
			}

			Shader::ShaderID Shader::createShader(ShaderType shaderType)
			{
				// Setup file extension depending on shaderType and also create OpenGL shader:
				std::string fileExtension;
				switch (shaderType)
				{
				case GL_VERTEX_SHADER:
					fileExtension = ".vert";
					break;
				case GL_FRAGMENT_SHADER:
					fileExtension = ".frag";
					break;
				default:
					break;
				}

				// Read Shader file
				ifs.open(m_ShaderPath + m_ShaderName + fileExtension);
				/*
				if (ifs.fail())
				{
					SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to open Shader : %s \n", (m_ShaderPath + m_ShaderName + fileExtension).c_str());
					exit(-1);
					return -1;
				}*/
				std::string shaderSource;
				std::string line;
				while (std::getline(ifs, line))
				{
					shaderSource.append(line + "\n");
				}

				ifs.close();

				// Create and Compile Shader (OpenGL)
				ShaderID shaderID = glCreateShader(shaderType);
				const char* shaderSource_cstr = shaderSource.c_str();
				glShaderSource(shaderID, 1, &shaderSource_cstr, NULL);
				glCompileShader(shaderID);

				GLint success = 0;
				glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					GLint maxLength = 0;
					glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

					// The maxLength includes the NULL character
					std::vector<char> errorLog(maxLength);
					glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

					// Provide the infolog in whatever manor you deem best.
					// Exit with failure.
					glDeleteShader(shaderID); // Don't leak the shader.

					SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Shader failed to compile [ %s ] : \n %s \n", (m_ShaderName + fileExtension).c_str(), &(errorLog[0]));

					return -1;
				}

				return shaderID;

			}
		}
	}
}