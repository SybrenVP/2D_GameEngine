#include "pch.h"
#include "InputComponent.h"


svp::InputComponent::InputComponent(GameObject* const pGameObject)
	: BaseComponent(pGameObject)
	, m_pBoundButtons{}
	, m_pBoundAxis{}
{
	InputManager::GetInstance().AddPlayer(this);
}


svp::InputComponent::~InputComponent()
{
	size_t size{ m_pBoundButtons.size() };
	for (size_t i{}; i < size; i++)
	{
		delete m_pBoundButtons.at(m_pBoundButtons.size() - 1)->m_pCommand;
		delete m_pBoundButtons.at(m_pBoundButtons.size() - 1);
		m_pBoundButtons.pop_back();
	}
	
	size_t sizeAxis{ m_pBoundAxis.size() };
	for (size_t i{}; i < sizeAxis; i++)
	{
		delete m_pBoundAxis.at(m_pBoundAxis.size() - 1)->second;
		delete m_pBoundAxis.at(m_pBoundAxis.size() - 1);
		m_pBoundAxis.pop_back();
	}
}

void svp::InputComponent::SetButton(SDL_GameControllerButton button, InputCommands* pCommand)
{
	for (size_t i{}; i < m_pBoundButtons.size(); i++)
	{
		if (m_pBoundButtons.at(i)->m_Button == button && m_pBoundButtons.at(i)->m_pCommand == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button and command are already in the list; In 'InputComponent::SetButton()'");
			return;
		}
		if (m_pBoundButtons.at(i)->m_Button == button)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button is already in use for another command; In 'InputComponent::SetButton()'.");
		}
		if (m_pBoundButtons.at(i)->m_pCommand == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Error, "This command is assigned to another button; In 'InputComponent::SetButton()'.");
			return;
		}
	}
	m_pBoundButtons.push_back(new Button(button, pCommand, true));
}

void svp::InputComponent::SetAxis(SDL_GameControllerAxis axis, InputCommands * pCommand)
{
	for (auto boundAxis : m_pBoundAxis)
	{
		if (boundAxis->first == axis && boundAxis->second == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This axis and command are already in the list; In 'InputComponent::SetAxis()'");
			return;
		}
		if (boundAxis->first == axis)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This axis is already in use for another command; In 'InputComponent::SetAxis()'.");
		}
		if (boundAxis->second == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Error, "This command is assigned to another axis; In 'InputComponent::SetAxis()'.");
			return;
		}
	}
	
	m_pBoundAxis.push_back(new std::pair<SDL_GameControllerAxis, InputCommands*>( axis, pCommand ));
}

void svp::InputComponent::ProcessCommands(SDL_GameControllerButton cButton, bool isUp)
{
	for (auto button : m_pBoundButtons)
	{
		if (button->m_Button == cButton)
		{
			button->bIsUp = isUp;
			if(!isUp)
				button->m_pCommand->Execute(m_pGameObject);
			
			break;
		}
	}

}

void svp::InputComponent::ProcessCommands(SDL_GameControllerAxis cAxis, const int value)
{
	for (auto axis : m_pBoundAxis)
	{
		if (axis->first == cAxis)
		{
			axis->second->Execute(m_pGameObject, value);
			return;
		}
	}
}

void svp::InputComponent::Update()
{
	for (auto button : m_pBoundButtons)
	{
		if (!button->bIsUp)
			button->m_pCommand->Execute(m_pGameObject);
	}
}

void svp::InputComponent::Render()
{
}
