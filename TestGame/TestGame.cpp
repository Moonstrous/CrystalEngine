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
		using namespace Crystal::Core;
		Action* jump = new Action();
		jump->actionName = "Jump";
		jump->keycode = SDL_SCANCODE_A;
		InputContext* movementContext = new InputContext();
		movementContext->contextName = "Movement";
		movementContext->inputMap.RegisterAction(jump);
		m_pEnv->pInputManager->RegisterInputContext(movementContext);
		m_pEnv->pInputManager->SwitchInputContext("Movement");
		ActionCallback* Jump = new ActionCallback([&](InputType type) {
			if (type == KeyDown)
			{
				m_pSprite1->Translate({ 50, 50 });
			}
		});
		m_pEnv->pInputManager->GetContext("Movement").OnAction("Jump", Jump);
		m_pSprite1 = new Crystal::Graphics::Renderable2D{ {50,50},{50,50},{0.5,1,0.2,1} };
		m_Shader.Bind();
		m_Shader.SetUniform("Projection", glm::ortho<float>(0, 800, 600, 0, -100, 100));
		m_Shader.Unbind();
	}

	virtual void update() override
	{
		if (m_pEnv->pInputManager->IsKeyDown(SDL_SCANCODE_D))
		{
			m_pSprite1->Translate({ 0,1 });
		}
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