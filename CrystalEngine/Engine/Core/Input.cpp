#include "Input.h"

namespace Crystal {
	namespace Core {
		InputManager& InputManager::RegisterInputContext(InputContext* inputContext)
		{
			m_pInputContextes.emplace(inputContext->contextName,inputContext);
			return *this;
		}
		InputManager& InputManager::SwitchInputContext(std::string contextName)
		{
			m_pCurrentInputContext = m_pInputContextes.at(contextName);
			return *this;
		}
		InputContext& InputManager::GetContext(std::string contextName)
		{
			return *(m_pInputContextes.at(contextName));
		}
		InputContext& InputManager::GetCurrentContext()
		{
			return *m_pCurrentInputContext;
		}
		void InputManager::DispatchKeyboard(InputType type, unsigned int keycode)
		{
			if (type == KeyDown || type == KeyUp)
			{
				m_Keys[keycode] = type;
				std::optional<Action*> action = m_pCurrentInputContext->inputMap.GetActionByKeycode(keycode);
				if (action)
				{
					Action* actionValue = *action;
					for (ActionCallback* callback : actionValue->GetCallbacks())
					{
						std::invoke(*callback,type);
					}
				}
				std::optional<Axis*> axis = m_pCurrentInputContext->inputMap.GetAxisByKeycode(keycode);
				if (axis)
				{
					Axis* axisValue = *axis;
					for (AxisCallback* callback : axisValue->GetCallbacks())
					{
						std::invoke(*callback, axisValue->axisValue);
					}
				}
			}
		}
		void InputManager::SetMouseState(const MouseState& newMouseState)
		{
			m_MouseState = newMouseState;
		}

		void InputManager::MouseMotion(const glm::vec2& newPosition)
		{
			m_MouseState.position = newPosition;
		}

		void InputManager::MouseButton(bool isDown)
		{
			m_MouseState.lmbDown = isDown;
		}

		bool InputManager::IsKeyDown(int keycode)
		{
			return m_Keys[keycode];
		}
		const MouseState& InputManager::GetMouseState()
		{
			return m_MouseState;
		}
		std::optional<Action*> InputContext::InputMap::GetActionByKeycode(int keycode)
		{
			for (std::pair<const std::string, Action*> actionPair : actions)
			{
				if (actionPair.second->keycode == keycode)
					return actionPair.second;
			}
			return {};
		}
		std::optional<Axis*> InputContext::InputMap::GetAxisByKeycode(int keycode)
		{
			for (std::pair<std::string, Axis*> axisPair : axis)
			{
				auto it = axisPair.second->axis.find(keycode);
				if (it != axisPair.second->axis.end())
				{
					return axisPair.second;
				}
			}
			return {};
		}
		void InputContext::OnAction(std::string actionName, ActionCallback* callback)
		{
			inputMap.actions.at(actionName)->callbacks->push_back(callback);
		}

		void InputContext::OnAxis(std::string axisName, AxisCallback* callback)
		{
			inputMap.axis.at(axisName)->callbacks->push_back(callback);
		}

	}
}