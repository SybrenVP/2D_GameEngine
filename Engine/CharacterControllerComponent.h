#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "InputComponent.h"

namespace svp
{

	class CharacterControllerComponent final : public BaseComponent
	{
	public:
		CharacterControllerComponent(GameObject* const pGameObject);
		virtual ~CharacterControllerComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }

		void SetButton(SDL_GameControllerButton button, InputCommands* pCommand);
		void SetAxis(SDL_GameControllerAxis button, InputCommands* pCommand);
	private:
		InputComponent* m_pInputComp;
	};
}