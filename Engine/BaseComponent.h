#pragma once
#include "GameObject.h"
#include "LayerFlags.h"
#include "Renderer.h"
//#include "TriggerComponent.h"

namespace svp
{
	class TriggerComponent;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* const pGameObject) : m_pGameObject{ pGameObject } {};
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void FixedUpdate() = 0;

		virtual LayerFlag GetLayerFlags()
		{
			return m_Layer;
		}

		virtual void OnTriggerEnter(TriggerComponent*) {}
		virtual void OnTriggerStay(TriggerComponent*) {}
		virtual void OnTriggerLeave(TriggerComponent*) {}

		GameObject* GetGameObject() { return m_pGameObject; }

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	protected:
		GameObject* const m_pGameObject;
		LayerFlag m_Layer = LayerFlag::Normal;
	};
}