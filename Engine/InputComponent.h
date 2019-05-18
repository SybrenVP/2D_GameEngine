#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "InputCommands.h"

namespace svp
{
	class Button
	{
	public:
		Button(SDL_GameControllerButton button, InputCommands* pCommand, bool isUp) : m_Button{ button }, m_pCommand{ pCommand }, bIsUp{ isUp } {}
		//ControllerButton m_Button;
		SDL_GameControllerButton m_Button;
		InputCommands* m_pCommand;
		bool bIsUp = true;
	};


	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(GameObject* const pGameObject);
		~InputComponent();

		void SetButton(SDL_GameControllerButton button, InputCommands* command);
		void SetAxis(SDL_GameControllerAxis axis, InputCommands* command);
		void ProcessCommands(SDL_GameControllerButton button, bool isUp = true );
		void ProcessCommands(SDL_GameControllerAxis axis, const int value = 0);

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }
	private:
		std::vector<Button*> m_pBoundButtons;
		std::vector<std::pair<SDL_GameControllerAxis, InputCommands*>*> m_pBoundAxis;
	};
}