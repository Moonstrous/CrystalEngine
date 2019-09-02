#define SDL_MAIN_HANDLED
#include "Application.h"

class TestApplication : public Crystal::Application
{
private:
	Crystal::Graphics::GL::Shader m_Shader{ "TestShader", "Shaders/" };
	Crystal::Graphics::Renderer2D m_Renderer{ glm::ortho<float>(0,800,600,0,-100,100) };
	Crystal::Graphics::Renderable2D* m_pSprite1;
public:
	TestApplication(const Arguments& args)
		:Application(args, Crystal::Application::Configuration{}.SetTitle("Test App").SetSize({800,600}))
	{

		Crystal::Core::Action* jump = new Crystal::Core::Action();
		jump->actionName = "Jump";
		jump->keycode = SDL_SCANCODE_A;
		Crystal::Core::InputContext* movementContext = new Crystal::Core::InputContext();
		movementContext->contextName = "Movement";
		movementContext->inputMap.RegisterAction(jump);
		m_pEnv->pInputManager->RegisterInputContext(movementContext);
		m_pEnv->pInputManager->SwitchInputContext("Movement");
		std::function<void(Crystal::Core::InputType)>* Jump = new std::function<void(Crystal::Core::InputType)>([&](Crystal::Core::InputType type) {
			m_pSprite1 = new Crystal::Graphics::Renderable2D{ {500,50},{50,50},{1,0,0.7,1} };
		});
		m_pEnv->pInputManager->GetContext("Movement").OnAction("Jump", Jump);
		m_pSprite1 = new Crystal::Graphics::Renderable2D{ {50,50},{50,50},{0.5,1,0.2,1} };
		m_Shader.Bind();
		m_Shader.SetUniform("Projection", glm::ortho<float>(0, 800, 600, 0, -100, 100));
		m_Shader.Unbind();
	}

	virtual void draw() override
	{
		GetWindow().Clear();
		m_Shader.Bind();
		m_Renderer.Begin();
		m_Renderer.Push(m_pSprite1);
		m_Renderer.End();
		m_Renderer.Flush();
		m_Shader.Unbind();
		GetWindow().SwapFrameBuffer();
	}
};

CRYSTAL_APPLICATION(TestApplication)