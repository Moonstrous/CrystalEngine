#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <functional>
#include <optional>
#include <SDL2/SDL.h>
#include "glm/vec2.hpp"

/*
	Example usage of Input API (for Context):
	// Application Constructor :
	// Most of this will be automated by loading and parsing an InputMap.json file (or smth)
	Action jump;
	jump.actionName = "Jump";
	jump.keyCode = SDLK_SPACEBAR;
	InputContext movementContext;
	movementContext.contextName = "Movement";
	movementContext.RegisterAction(&jump);
	m_pEnv->pInputManager->RegisterInputContext(&movementContext);
	m_pEnv->pInputManager->SwitchInputContext("Movement");
	// Example player class :
	class Player : public Entity,IInputListener
	{
		void RegisterInputListener(InputManager* inputManager) override
		{
			inputManager->GetContext("Movement")->OnAction("Jump",LAMBDA_FUNCTION_FOR_JUMP);
			inputManager->OnMouseMoved(LAMBDA_FOR_MOUSE_MOVEMENT);
		}
	}
*/

namespace Crystal {
	namespace Core {


		enum InputType : char
		{
			KeyUp = 0,
			KeyDown = 1,
			KeyHeld,
			Modifier
		};

		using ActionCallback = std::function<void(InputType)>;
		using AxisCallback = std::function<void(float)>;

		struct Action
		{
			Action() : callbacks(new std::vector<ActionCallback*>()) {}
			std::string actionName;
			int keycode;
			std::vector<ActionCallback*>* callbacks;
			std::vector<ActionCallback*>& GetCallbacks()
			{
				return *callbacks;
			}
		};

		struct Axis
		{
			Axis() : callbacks(new std::vector<AxisCallback*>()) {}
			std::string axisName;
			std::unordered_map<int,float> axis;
			float axisValue = 0.0f;
			std::vector<AxisCallback*>* callbacks;
			std::vector<AxisCallback*>& GetCallbacks()
			{
				return *callbacks;
			}
		};


		struct InputContext
		{
			std::string contextName;
			struct InputMap
			{
				std::unordered_map<std::string,Action*> actions;
				std::unordered_map<std::string,Axis*> axis;

				std::optional<Action*> GetActionByKeycode(int keycode);
				std::optional<Axis*> GetAxisByKeycode(int keycode);

				void RegisterAction(Action* action) 
				{
					actions.emplace(action->actionName, action);
				}
			} inputMap;

			void OnAction(std::string actionName, ActionCallback* callback);
			void OnAxis(std::string axisName, AxisCallback* callback);

		};

		struct MouseState
		{
			glm::vec2 position;
			bool lmbDown;
			float scrollDelta;
		};

		class InputManager
		{
		private:
			InputContext* m_pCurrentInputContext;
			std::map<std::string,InputContext*> m_pInputContextes;
			unsigned int m_Keys[320];
			MouseState m_MouseState;
		public:
			InputManager() {}
			~InputManager() { delete m_pCurrentInputContext; }
			//void RegisterInputListener(IInputListener* inputListener);
			InputManager& RegisterInputContext(InputContext* inputContext);
			InputManager& SwitchInputContext(std::string contextName);
			InputContext& GetContext(std::string contextName);
			InputContext& GetCurrentContext();
			void DispatchKeyboard(InputType type, unsigned int keycode);
			void SetMouseState(const MouseState& newMouseState);
			void MouseMotion(const glm::vec2& newPosition);
			void MouseButton(bool isDown);
			// Poll-based Input :
			bool IsKeyDown(int keycode);
			const MouseState& GetMouseState();
		};

	}
}