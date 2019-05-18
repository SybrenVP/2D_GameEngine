#pragma once
#include "Singleton.h"
namespace svp
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(Scene* pScene);

		void Initialize();
		void Update();
		void FixedUpdate(); //Needs to use GameTime::m_MsPerUpdate as time instead of deltaTime.
		void Render();

		virtual ~SceneManager();

	private:
		std::vector<Scene*> m_pScenes;
	};
}