#pragma once
#include "SceneManager.h"

namespace svp
{
	class GameObject;

	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);

		void Add(GameObject* pObject);

		virtual void Initialize();
		virtual void Update();
		virtual void Render() const;
		virtual void FixedUpdate();
		
		std::string GetName() const { return m_Name; }
		std::vector<GameObject*> GetGameObjects() { return m_pGameObjects; }

		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		bool operator==(const Scene& other) const { return (m_Name == other.m_Name); }

	protected:
		std::string m_Name;
		std::vector<GameObject*> m_pGameObjects;
		static unsigned int idCounter;
	};
}