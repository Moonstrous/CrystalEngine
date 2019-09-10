#pragma once
#include "Input.h"
#include "ResourceManager.h"

namespace Crystal {
	namespace Core {
		struct Environment
		{
			InputManager* pInputManager;
			ResourceManager* pResourceManager;
		};
	}
}