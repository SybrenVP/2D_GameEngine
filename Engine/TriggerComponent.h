#pragma once
#include "BaseComponent.h"
#include <map>
namespace svp
{
	class Scene;

	class TriggerComponent final : public BaseComponent
	{
	public:
		TriggerComponent(GameObject* const pGameObject, float width, float height, float xOffset = 0.f, float yOffset = 0.f, LayerFlag onLayer = LayerFlag::Trigger);
		~TriggerComponent() = default;

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override;

		void TriggerEnter(TriggerComponent* pOther);
		void TriggerLeave(TriggerComponent* pOther);

	private:
		float m_Width;
		float m_Height;
		float m_XOffset;
		float m_YOffset;
		std::map<GameObject*, bool> m_pIsInTrigger;

		LayerFlag m_OnLayer;

		bool InsideTrigger(Transform pOther);

		//Vars to keep it optimized
		Scene* m_pActiveScene;
		std::vector<GameObject*> m_pCharacterGameObjects;
	};
}
