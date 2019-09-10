#include "Application.h"

#include <chrono>

namespace Crystal {

	const static double MS_PER_UPDATE = 0.016;
	
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
		std::chrono::high_resolution_clock::time_point prev = std::chrono::high_resolution_clock::now();
		double lag = 0.0;
		while (!m_ShouldQuit)
		{
			std::chrono::high_resolution_clock::time_point curr = std::chrono::high_resolution_clock::now();
			double elapsed = std::chrono::duration<double>(curr - prev).count();
			prev = curr;
			lag += elapsed;
			applicationUpdate();
			while (lag >= MS_PER_UPDATE)
			{
				update(elapsed);
				lag -= MS_PER_UPDATE;
			}
			draw();
		}
		return 1;
	}
	void Application::applicationUpdate()
	{
		SDL_PollEvent(&m_pE);
		switch (m_pE.type)
		{
		case SDL_EventType::SDL_QUIT:
			m_ShouldQuit = true;
			break;
		case SDL_EventType::SDL_KEYDOWN:
			if (!m_pE.key.repeat)
			{
				m_pEnv->pInputManager->DispatchKeyboard(Core::InputType::KeyDown, m_pE.key.keysym.scancode); // Maybe switch to scan code ?
			}
			break;
		case SDL_EventType::SDL_KEYUP:
			if (!m_pE.key.repeat)
			{
				m_pEnv->pInputManager->DispatchKeyboard(Core::InputType::KeyUp, m_pE.key.keysym.scancode); // Maybe switch to scan code ?
			}
			break;
		case SDL_EventType::SDL_MOUSEMOTION:
			m_pEnv->pInputManager->MouseMotion({ m_pE.motion.x, m_pE.motion.y });
			break;
		case SDL_EventType::SDL_MOUSEBUTTONDOWN:
			m_pEnv->pInputManager->MouseButton(true);
			break;
		case SDL_EventType::SDL_MOUSEBUTTONUP:
			m_pEnv->pInputManager->MouseButton(false);
			break;
		case SDL_EventType::SDL_MOUSEWHEEL:
			break;
		default:
			break;
		}
	}

	void Application::update(double dt)
	{
	}

	void Application::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pWindow->SwapFrameBuffer();
	}
}
