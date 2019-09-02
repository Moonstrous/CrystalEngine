#include "Application.h"


namespace Crystal {

	Application::Configuration::Configuration()
	{
		m_Title = "Untitled - Crystal Application";
		m_Size = { 800,600 };
		m_Flags = Core::Window::WindowFlags::Shown;
		m_BackgroundColor = glm::vec4(0, 0, 0, 1);
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

	const glm::vec4& Application::Configuration::GetBackgroundColor()
	{
		return m_BackgroundColor;
	}

	Application::Configuration& Application::Configuration::SetBackgroundColor(const glm::vec4& color)
	{
		m_BackgroundColor = color;
		glClearColor(color.r, color.g, color.b, color.a);
		return *this;
	}

	Application::Application(const Application::Arguments& args, const Application::Configuration& config)
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
		glm::vec4 bgColor = m_AppConfig.GetBackgroundColor();
		glClearColor(bgColor.r,bgColor.g,bgColor.b,bgColor.a);
		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0);
		glViewport(0, 0, m_AppConfig.GetSize().x, m_AppConfig.GetSize().y);		

		m_pEnv = new Core::Environment();
		m_pEnv->pInputManager = new Core::InputManager();
	}

	Application::~Application()
	{
	}

	int Application::Exec()
	{
		m_pWindow->Show();

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
		case SDL_EventType::SDL_KEYDOWN:
			m_pEnv->pInputManager->DispatchKeyboard(Core::InputType::KeyDown, m_pE.key.keysym.scancode); // Maybe switch to scan code ?
			break;
		case SDL_EventType::SDL_KEYUP:
			m_pEnv->pInputManager->DispatchKeyboard(Core::InputType::KeyUp, m_pE.key.keysym.scancode); // Maybe switch to scan code ?
			break;
		default:
			break;
		}
	}
	void Application::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pWindow->SwapFrameBuffer();
	}
}
