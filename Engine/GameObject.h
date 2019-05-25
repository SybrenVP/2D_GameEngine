#pragma once
#include <memory>
//#include "BaseComponent.h"
#include "TransformComponent.h"


namespace svp
{
	class BaseComponent;

	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();

		void Update();
		void Render() const;
		void FixedUpdate();

		void AddComponent(BaseComponent* pComponent);
		void SetPosition(float x, float y);
		void Translate(float x, float y);
		
		Transform GetTransform() { return m_Transform; }

		template <class T>
		T* GetComponent() //see Overlord implementation
		{
			const type_info& type{ typeid(T) };
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == type)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		template <class T>
		std::vector<T*> GetComponents()
		{
			const type_info& type{ typeid(T) };
			std::vector<type> components;

			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == type)
					components.push_back(static_cast<T*>(component));
			}
			if (components)
				return components;
			else
				return nullptr;
		}

		std::vector<BaseComponent*> GetAllComponents()
		{
			return m_pComponents;
		}
		void SetActive(bool active) { m_Active = active; }

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform{ };
		std::vector<BaseComponent*> m_pComponents;
		bool m_Active = true;
	};
}