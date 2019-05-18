#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "InputCommands.h"

namespace svp
{
	class CButton
	{
	public:
		CButton(SDL_GameControllerButton button, InputCommands* pCommand, bool isUp) : m_Button{ button }, m_pCommand{ pCommand }, bIsUp{ isUp } {}
		SDL_GameControllerButton m_Button;
		InputCommands* m_pCommand;
		bool bIsUp = true;
	};

	class KButton
	{
	public:
		KButton(SDL_Keycode button, InputCommands* pCommand, bool isUp) : m_Button{ button }, m_pCommand{ pCommand }, bIsUp{ isUp } {}
		SDL_Keycode m_Button;
		InputCommands* m_pCommand;
		bool bIsUp = true;
	};


	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(GameObject* const pGameObject);
		~InputComponent();

		void SetButton(SDL_GameControllerButton button, InputCommands* command);
		void SetButton(SDL_Scancode key, InputCommands* command);
		
		void ProcessCommands(SDL_GameControllerButton button, bool isUp = true);
		void ProcessCommands(SDL_Scancode button, bool isUp = true);

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }
	private:
		std::vector<CButton*> m_pBoundCButtons;
		std::vector<KButton*> m_pBoundKButtons;
	};
}