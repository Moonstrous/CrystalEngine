#pragma once
#include "Resource.h"
#include "ResourceManager.h"

/*
	Factory API Example : 
	ShaderResource diffuseShader = m_pEnv->pResourceManager->GetFactory("ShaderFactory")->CreateResource("Diffuse Shader");
	will return a ShaderResource which holds meta-data and points to a shader object, there is also a ref count so: 
	Renderer->Use(diffuseShader); will inc refCount. and We ALWAYS check if the resource is already loaded (caching)
	m_pEnv->pResourceManager->GetFactory("ShaderFactory")->ReloadResource("Diffuse Shader");
	will reload and update the resource in a Hot Reload kind of fashion.
*/

namespace Crystal {
	namespace Core {

		class IFactory
		{
		protected:
			ResourceManager* m_pResourceManager;
		public:
			IFactory() = default;
			virtual Resource* LoadResource(const std::string& resourceName) = 0;
			virtual bool ReloadResource(const std::string& resourceName) = 0;
			void SetResourceManager(ResourceManager* pResourceManager) { m_pResourceManager = pResourceManager; }
		};
	}
}

