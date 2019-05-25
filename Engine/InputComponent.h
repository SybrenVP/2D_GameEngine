#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "InputCommands.h"

namespace svp
{
	class CButton
	{
	public:
		CButton(SDL_GameControllerButton button, InputCommands* pCommand, bool isUp, bool useOnDown) : m_Button{ button }, m_pCommand{ pCommand }, bIsUp{ isUp }, bUseOnDown{ useOnDown } {}
		SDL_GameControllerButton m_Button;
		InputCommands* m_pCommand;
		bool bUseOnDown = true;
		bool bIsUp = true;
		bool bWasUp = true;
	};

	class KButton
	{
	public:
		KButton(SDL_Keycode button, InputCommands* pCommand, bool isUp, bool useOnDown) : m_Button{ button }, m_pCommand{ pCommand }, bIsUp{ isUp }, bUseOnDown{ useOnDown } {}
		SDL_Keycode m_Button;
		InputCommands* m_pCommand;
		bool bUseOnDown = true;
		bool bIsUp = true;
		bool bWasUp = true;
	};


	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(GameObject* const pGameObject, bool isKeyboard = false);
		~InputComponent();

		void SetButton(SDL_GameControllerButton button, InputCommands* command, bool down = true);
		void SetButton(SDL_Scancode key, InputCommands* command, bool down = true);
		
		void ProcessCommands(SDL_GameControllerButton button, bool isUp = true);
		void ProcessCommands(SDL_Scancode button, bool isUp = true);

		bool GetIsKeyBoard() { return m_IsKeyboard; }

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }
	private:
		std::vector<CButton*> m_pBoundCButtons;
		std::vector<KButton*> m_pBoundKButtons;

		bool m_IsKeyboard;
	};
}