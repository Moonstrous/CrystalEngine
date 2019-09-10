#pragma once
#include "Engine/Core/Window.h"
#include "Engine/Core/Environment.h"

#include "vendor/glad/glad.h"

#include "Engine/Graphics/Renderer2D.h"
#include "Engine/Graphics/Renderable2D.h"

#define CRYSTAL_APPLICATION(applicationClass) int main(int argc,char** argv) \
												{\
													applicationClass* app = new applicationClass({argc,argv});\
													return app->Exec();\
												}\

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
			glm::vec4 m_BackgroundColor;
		public:
			Configuration();

			std::string GetTitle();
			Configuration& SetTitle(const std::string& title);
			const glm::vec2& GetSize();
			Configuration& SetSize(const glm::vec2& size);
			const Core::Window::WindowFlags& GetFlags();
			Configuration& SetFlags(const Core::Window::WindowFlags& flags);
			const glm::vec4& GetBackgroundColor();
			Configuration& SetBackgroundColor(const glm::vec4& color);
		};

	private:
		SDL_Event m_pE;
		bool m_ShouldQuit = false;
	protected:
		Core::Environment* m_pEnv;
		Core::Window* m_pWindow;
		Configuration m_AppConfig;
		Arguments m_Arguments;

	public:
		Application(const Arguments& args, const Configuration& config = Configuration());
		~Application();

		int Exec();

		Core::Environment* GetEnv() { return m_pEnv; }

		/* GETTERS */
		Crystal::Core::Window& GetWindow() { return *m_pWindow; }
		Configuration& GetAppConfig() { return m_AppConfig; }
		
	private:
		void applicationUpdate();
	protected:
		virtual void update(double dt);
		virtual void draw();
	};

}
