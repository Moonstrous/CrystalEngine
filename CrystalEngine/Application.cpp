#include "Application.h"


namespace Crystal {

	Application::Configuration::Configuration()
	{
		m_Title = "Untitled - Crystal Application";
		m_Size = { 800,600 };
		m_Flags = Core::Window::WindowFlags::Shown;
	}

	std::string Application::Configuration::GetTitle()
	{
		return m_Title;
	}

	Crystal::Application::Configuration& Application::Configuration::SetTitle(const std::string& title)
	{
		m_Title = title;
		return *this;
	}


	const glm::vec2& Application::Configuration::GetSize()
	{
		return m_Size;
	}

	Application::Configuration& Application::Configuration::SetSize(const glm::vec2& size)
	{
		m_Size = size;
		return *this;
	}

	const Core::Window::WindowFlags& Application::Configuration::GetFlags()
	{
		return m_Flags;
	}

	Application::Configuration& Application::Configuration::SetFlags(const Core::Window::WindowFlags& flags)
	{
		m_Flags = flags;
		return *this;
	}

	Application::Application(const Arguments& args, const Configuration& config)
		:m_Arguments(args),m_AppConfig(config)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL2 : %s \n", SDL_GetError()); exit(-1);
		}
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		m_pWindow = new Core::Window(m_AppConfig.GetTitle(), m_AppConfig.GetSize(), m_AppConfig.GetFlags());
		glClearColor(0.8, 0.8, 0.8, 1);
		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0);
		glViewport(0, 0, m_AppConfig.GetSize().x, m_AppConfig.GetSize().y);

		m_pRenderer = new Graphics::Renderer2D(glm::ortho(0.0f,800.0f, 600.0f,0.0f,-100.0f,100.0f));
		
	}

	Application::~Application()
	{
	}

	int Application::Exec()
	{
		m_pWindow->Show();

		// TEMPORARY TESTING CODE |BEGIN :
		m_pShader = new Graphics::GL::Shader("TestShader","Shaders/");
		m_pShader->AddAttribute("position");
		m_pShader->AddAttribute("color");
		m_pShader->Bind();
		m_pShader->SetUniform("Projection", glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -100.0f, 100.0f));
		m_pShader->Unbind();

		sprite1 = new Graphics::Renderable2D{ glm::vec2(80, 80), glm::vec2(80, 80), glm::vec4(1, 1, 1, 1) };
		sprite2 = new Graphics::Renderable2D{ glm::vec2(200, 200), glm::vec2(100, 100), glm::vec4(1, 1, 1, 1) };
		// TEMPORARY TESTING CODE |END

		while (!m_ShouldQuit) // TODO : Proper Application Loop
		{
			update();
			draw();
		}
		return 1;
	}
	void Application::update()
	{
		SDL_PollEvent(&m_pE);
		switch (m_pE.type)
		{
		case SDL_EventType::SDL_QUIT:
			m_ShouldQuit = true;
			break;
		default:
			break;
		}
	}
	void Application::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// TEMPORARY TESTING CODE |BEGIN :
		m_pShader->Bind();
		m_pRenderer->Begin();
		m_pRenderer->Push(sprite1);
		m_pRenderer->Push(sprite2);
		m_pRenderer->End();
		m_pRenderer->Flush();
		m_pShader->Unbind();
		// TEMPORARY TESTING CODE |END
		m_pWindow->SwapFrameBuffer();
	}
}
