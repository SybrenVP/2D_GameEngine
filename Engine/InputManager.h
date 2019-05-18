#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL_gamecontroller.h"
#include "SDL_events.h"

namespace svp
{
	class InputComponent;

	//enum class ControllerButton
	//{
	//	A,
	//	B,
	//	X,
	//	Y,
	//	LeftShoulder,
	//	RightShoulder,
	//	StickLeft,
	//	StickRight,
	//	DPadLeft,
	//	DPadRight,
	//	DPadUp,
	//	DPadDown
	//};

	//enum class ControllerAxis
	//{
	//	LeftX,
	//	LeftY,
	//	RightX,
	//	RightY,
	//	TriggerLeft,
	//	TriggerRight
	//};

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
		void ProcessCAxis(const SDL_ControllerAxisEvent cAxis, const int playerID = 0, const int value = 0);

	private:
		std::vector<InputComponent*> m_pPlayers;
		std::vector<SDL_GameController*> m_pControllers;

		static const int m_JoystickDeadzone;
	};
}
