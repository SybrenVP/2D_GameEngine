#include "pch.h"
#include "InputManager.h"
#include "InputComponent.h"
#include <SDL.h>

const int svp::InputManager::m_JoystickDeadzone{ 8000 };

void svp::InputManager::Initialize()
{
	//Check for controllers
	if (SDL_NumJoysticks() < 1)
		Logger::GetInstance().Log(Logger::LogType::Warning, "No controller connected!");
	else
	{
		std::string debugText{ "Found " + std::to_string(int(SDL_NumJoysticks())) };
		debugText += " controllers.";
		Logger::GetInstance().Log(Logger::LogType::Debug, debugText);

		//Load controllers
		for (int i{}; i < SDL_NumJoysticks(); i++)
		{
			m_pControllers.push_back(NULL);
			m_pControllers.at(i) = SDL_GameControllerOpen(i);
			if (!m_pControllers.at(i))
			{
				Logger::GetInstance().Log(Logger::LogType::Error, "Unable to open controller! Nr. " + std::to_string(i));
			}
#ifdef DEBUG
			Logger::GetInstance().Log(Logger::LogType::Debug, "Opened controller " + std::to_string(i));
#endif
		}	
		
	}
}

void svp::InputManager::CloseControllers()
{
	for (int i{}; i < SDL_NumJoysticks(); i++)
	{
		SDL_GameControllerClose(m_pControllers.at(i));
		m_pControllers.at(i) = NULL;
	}
}

bool svp::InputManager::IsNotQuitting()
{
	SDL_Event e{};
	
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			return false;
		else if (e.type == SDL_CONTROLLERBUTTONUP)
		{
			ProcessCButtonUp(e.cbutton, e.caxis.which);
		}
		else if (e.type == SDL_CONTROLLERBUTTONDOWN)
		{
			ProcessCButtonDown(e.cbutton, e.caxis.which);
		}
		else if (e.type == SDL_KEYUP)
		{
			ProcessKButtonUp(e.key, 0);
		}
		else if (e.type == SDL_KEYDOWN)
		{
			ProcessKButtonDown(e.key, 0);
		}
	}
	
	return true;
}

bool svp::InputManager::IsPressed(SDL_GameControllerButton) const
{
	return false;
}

void svp::InputManager::AddPlayer(InputComponent* pPlayer)
{
	m_pPlayers.push_back(pPlayer);
}

void svp::InputManager::ProcessCButtonUp(const SDL_ControllerButtonEvent cButton, const int playerID)
{
	if (playerID > int(m_pPlayers.size()) - 1)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "playerID larger than amount of players; In 'InputManager::ProcessCButtonUp()'.");
		return;
	}

	m_pPlayers.at(playerID)->ProcessCommands(SDL_GameControllerButton(cButton.button));
}

void svp::InputManager::ProcessCButtonDown(const SDL_ControllerButtonEvent cButton, const int playerID)
{
	if (playerID > int(m_pPlayers.size()) - 1)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "playerID larger than amount of players; In 'InputManager::ProcessCButtonDown()'.");
		return;
	}

	m_pPlayers.at(playerID)->ProcessCommands(SDL_GameControllerButton(cButton.button), false);
}

void svp::InputManager::ProcessKButtonUp(const SDL_KeyboardEvent kButton, const int playerID)
{
	if (playerID > int(m_pPlayers.size()) - 1)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "playerID larger than amount of players; In 'InputManager::ProcessKButtonUP()'.");
		return;
	}

	m_pPlayers.at(playerID)->ProcessCommands(kButton.keysym.scancode, true);
}

void svp::InputManager::ProcessKButtonDown(const SDL_KeyboardEvent kButton, const int playerID)
{
	if (playerID > int(m_pPlayers.size()) - 1)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "playerID larger than amount of players; In 'InputManager::ProcessKButtonDown()'.");
		return;
	}

	m_pPlayers.at(playerID)->ProcessCommands(kButton.keysym.scancode, false);
}
