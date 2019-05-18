#pragma once
#include <memory>

#include "BaseComponent.h"
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

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform{ };
		std::vector<BaseComponent*> m_pComponents;
	};
}