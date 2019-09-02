#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <glm/vec2.hpp>

namespace Crystal {
	namespace Core {
		
		class Window
		{
		public:
			enum WindowFlags {
				Shown = SDL_WindowFlags::SDL_WINDOW_SHOWN,
				Fullscreen = SDL_WindowFlags::SDL_WINDOW_FULLSCREEN,
				Resizable = SDL_WindowFlags::SDL_WINDOW_RESIZABLE
			};
		private:
			SDL_Window* m_pWindow;
			std::string m_Title;
			glm::vec2 m_Size;
			WindowFlags m_Flags;
		public:
			Window(std::string title, glm::vec2 size = glm::vec2(800, 600), WindowFlags flags = WindowFlags::Shown);
			~Window();

			Window& Show() { SDL_ShowWindow(m_pWindow); return *this; }
			Window& Hide() { SDL_HideWindow(m_pWindow); return *this; }

			Window& Clear();
			Window& SwapFrameBuffer() { SDL_GL_SwapWindow(m_pWindow); return *this; }

			std::string GetTitle() { return m_Title; }
			Window& SetTitle(std::string title) { m_Title = title; return *this; }

		};

	}
}