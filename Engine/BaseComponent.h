#pragma once
#include "GameObject.h"
#include "Renderer.h"
namespace svp
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* const pGameObject) : m_pGameObject{ pGameObject } {};
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void FixedUpdate() = 0;

		GameObject* GetGameObject() { return m_pGameObject; };

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	protected:
		GameObject* const m_pGameObject;
	};
}