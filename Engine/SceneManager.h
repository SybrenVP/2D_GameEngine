#pragma once
#include "Singleton.h"
#include <map>
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
		
		void SetActiveScene();

		Scene* GetActiveScene() 
		{
			return m_pScenes[m_ActiveScene];
		}

		bool GoingToSwitchScene() { return m_SwitchScene; }
		void SwitchScene(std::string name);

		virtual ~SceneManager();

	private:
		std::map<std::string, Scene*> m_pScenes;
		std::vector<std::string> m_SceneNames;
		std::string m_ActiveScene;
		std::string m_NewActiveScene;
		bool m_SwitchScene;
	};
}