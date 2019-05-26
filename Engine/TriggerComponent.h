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
		void ScaleWidth(float width) { m_Width *= width; }
		void ScaleHeigth(float height) { m_Height *= height; }
		void SetOffset(float x, float y) 
		{
			m_XOffset = x;
			m_YOffset = y;
		}
		void SetActive(bool val) { m_Active = val; }
	private:
		float m_Width;
		float m_Height;
		float m_XOffset;
		float m_YOffset;
		bool m_Active;
		std::map<GameObject*, bool> m_pIsInTrigger;

		LayerFlag m_OnLayer;

		bool InsideTrigger(Transform pOther);

		//Vars to keep it optimized
		Scene* m_pActiveScene;
		std::vector<GameObject*> m_pCharacterGameObjects;
	};
}
