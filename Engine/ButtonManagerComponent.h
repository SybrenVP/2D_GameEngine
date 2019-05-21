#pragma once
#include "BaseComponent.h"

namespace svp
{
	class ButtonComponent;

	class ButtonManagerComponent final : public BaseComponent
	{
	public:
		ButtonManagerComponent(GameObject* const pGameObject, std::vector<ButtonComponent*> pButtons);
		virtual ~ButtonManagerComponent() = default;

		virtual void Update() override {}
		virtual void Render() override {}
		virtual void FixedUpdate() override {}

		void NextRight();
		void NextLeft();
		void NextUp();
		void NextDown();
		void Submit();

	private: 
		std::vector<ButtonComponent*> m_pButtons;
		int m_CurrentlySelected;

		void UpdateSelected();
	};
}

