#include "Window.h"
#include "vendor/glad/glad.h"

namespace Crystal {
	namespace Core {
		Window::Window(std::string title, glm::vec2 size, WindowFlags flags)
			:m_Title(title), m_Size(size), m_Flags(flags)
		{
			m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags | SDL_WindowFlags::SDL_WINDOW_OPENGL);
			if (!m_pWindow)
			{
				SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create SDL2 Window : %s \n", SDL_GetError()); exit(-1);
			}
			SDL_GL_CreateContext(m_pWindow);

			if (!gladLoadGL())
			{
				SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to initialize GLAD : %s \n", glad_glGetError()); exit(-1);
			}
			SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OpenGL Version : %d.%d \n", GLVersion.major, GLVersion.minor);
			
		}

		Window::~Window()
		{
			SDL_DestroyWindow(m_pWindow);
			m_pWindow = nullptr;
		}

		Window& Window::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			return *this;
		}

	}
}