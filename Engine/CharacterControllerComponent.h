#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "InputComponent.h"

namespace svp
{

	class CharacterControllerComponent final : public BaseComponent
	{
	public:
		CharacterControllerComponent(GameObject* const pGameObject, bool isKeyboard = false);
		virtual ~CharacterControllerComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }

		void SetButton(SDL_GameControllerButton button, InputCommands* pCommand, bool down = true);
		void SetButton(SDL_Scancode, InputCommands* pCommand, bool down = true);
	private:
		InputComponent* m_pInputComp;
	};
}