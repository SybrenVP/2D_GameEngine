#include "pch.h"
#include "InputComponent.h"


svp::InputComponent::InputComponent(GameObject* const pGameObject, bool isKeyboard)
	: BaseComponent(pGameObject)
	, m_pBoundCButtons{}
	, m_IsKeyboard{isKeyboard}
{
	InputManager::GetInstance().AddPlayer(this);
}


svp::InputComponent::~InputComponent()
{
	size_t sizeC{ m_pBoundCButtons.size() };
	for (size_t i{}; i < sizeC; i++)
	{
		delete m_pBoundCButtons.at(m_pBoundCButtons.size() - 1)->m_pCommand;
		delete m_pBoundCButtons.at(m_pBoundCButtons.size() - 1);
		m_pBoundCButtons.pop_back();
	}

	size_t sizeK{ m_pBoundKButtons.size() };
	for (size_t i{}; i < sizeK; i++)
	{
		delete m_pBoundKButtons.at(m_pBoundKButtons.size() - 1)->m_pCommand;
		delete m_pBoundKButtons.at(m_pBoundKButtons.size() - 1);
		m_pBoundKButtons.pop_back();
	}
}

void svp::InputComponent::SetButton(SDL_GameControllerButton button, InputCommands* pCommand, bool down)
{
	for (size_t i{}; i < m_pBoundCButtons.size(); i++)
	{
		if (m_pBoundCButtons.at(i)->m_Button == button && m_pBoundCButtons.at(i)->m_pCommand == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button and command are already in the list; In 'InputComponent::SetButton()'");
			return;
		}
		if (m_pBoundCButtons.at(i)->m_Button == button)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button is already in use for another command; In 'InputComponent::SetButton()'.");
		}
	}
	m_pBoundCButtons.push_back(new CButton(button, pCommand, true, down));
}

void svp::InputComponent::SetButton(SDL_Scancode key, InputCommands* pCommand, bool down)
{
	for (size_t i{}; i < m_pBoundKButtons.size(); i++)
	{
		if (m_pBoundKButtons.at(i)->m_Button == key && m_pBoundKButtons.at(i)->m_pCommand == pCommand)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button and command are already in the list; In 'InputComponent::SetButton()'");
			return;
		}
		if (m_pBoundKButtons.at(i)->m_Button == key)
		{
			Logger::GetInstance().Log(Logger::LogType::Warning, "This button is already in use for another command; In 'InputComponent::SetButton()'.");
		}
	}
	m_pBoundKButtons.push_back(new KButton(key, pCommand, true, down));
}

void svp::InputComponent::ProcessCommands(SDL_GameControllerButton cButton, bool isUp)
{
	for (auto button : m_pBoundCButtons)
	{
		if (button->m_Button == cButton)
		{
			button->bIsUp = isUp;
			if(isUp == !button->bUseOnDown)
				button->m_pCommand->Execute(m_pGameObject);
		}
	}

}

void svp::InputComponent::ProcessCommands(SDL_Scancode kButton, bool isUp)
{
	for (auto button : m_pBoundKButtons)
	{
		if (button->m_Button == kButton)
		{
			button->bIsUp = isUp;
			if(isUp)
				if (isUp == !button->bUseOnDown)
					button->m_pCommand->Execute(m_pGameObject);
		}
	}
}

void svp::InputComponent::Update()
{
	for (auto button : m_pBoundCButtons)
	{
		if (button->bIsUp == !button->bUseOnDown && button->bWasUp != button->bIsUp)
			button->m_pCommand->Execute(m_pGameObject);
	}

	for (auto button : m_pBoundKButtons)
	{
		if ((button->bIsUp == !button->bUseOnDown) && (button->bWasUp != button->bIsUp))
			button->m_pCommand->Execute(m_pGameObject);
	}
}

void svp::InputComponent::Render()
{
}
