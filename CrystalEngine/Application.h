#pragma once
#include "Engine/Core/Window.h"
#include "vendor/glad/glad.h"

#include "Engine/Graphics/Renderer2D.h"
#include "Engine/Graphics/Renderable2D.h"

namespace Crystal {
	
	class Application
	{
	public:
		struct Arguments
		{
			Arguments(int argc,char** argv): Argc(argc),Argv(argv) {}
			int Argc;
			char** Argv;
		};

		struct Configuration
		{
		private:
			std::string m_Title;
			glm::vec2 m_Size;
			Core::Window::WindowFlags m_Flags;
			
		public:
			Configuration();

			std::string GetTitle();
			Configuration& SetTitle(const std::string& title);
			const glm::vec2& GetSize();
			Configuration& SetSize(const glm::vec2& size);
			const Core::Window::WindowFlags& GetFlags();
			Configuration& SetFlags(const Core::Window::WindowFlags& flags);
		};
	private:
		Core::Window* m_pWindow;
		Graphics::Renderer2D* m_pRenderer;
		Configuration m_AppConfig;
		Arguments m_Arguments;
		SDL_Event m_pE;
		bool m_ShouldQuit = false;

		//TEMP:
		Graphics::GL::Shader* m_pShader;
		Graphics::Renderable2D* sprite1;
		Graphics::Renderable2D* sprite2;

	public:
		Application(const Arguments& args, const Configuration& config = Configuration());
		~Application();

		int Exec();

	private:
		void update();
		void draw();
	};

}
