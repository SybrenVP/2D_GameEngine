#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_gamecontroller.h"
#include "SDL_events.h"

namespace svp
{
	class InputComponent;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Initialize();
		void CloseControllers();
		bool IsNotQuitting();
		bool IsPressed(SDL_GameControllerButton button) const;
		void AddPlayer(InputComponent * pPlayer);

		void ProcessCButtonUp(const SDL_ControllerButtonEvent cButton, const int playerID = 0);
		void ProcessCButtonDown(const SDL_ControllerButtonEvent cButton, const int playerID = 0);

		void ProcessKButtonUp(const SDL_KeyboardEvent kButton, const int playerID = 0);
		void ProcessKButtonDown(const SDL_KeyboardEvent kButton, const int playerID = 0);

	private:
		std::vector<InputComponent*> m_pPlayers;
		std::vector<SDL_GameController*> m_pControllers;

		static const int m_JoystickDeadzone;
	};
}
