#include "pch.h"
#include "ButtonManagerComponent.h"
#include "ButtonComponent.h"

svp::ButtonManagerComponent::ButtonManagerComponent(GameObject * const pGameObject, std::vector<ButtonComponent*> pButtons)
	: BaseComponent(pGameObject)
	, m_pButtons(pButtons)
{
}

void svp::ButtonManagerComponent::NextRight()
{
	m_pButtons[m_CurrentlySelected]->Right();
	UpdateSelected();
}

void svp::ButtonManagerComponent::NextLeft()
{
	m_pButtons[m_CurrentlySelected]->Left();
	UpdateSelected();
}

void svp::ButtonManagerComponent::NextUp()
{
	m_pButtons[m_CurrentlySelected]->Up();
	UpdateSelected();
}

void svp::ButtonManagerComponent::NextDown()
{
	m_pButtons[m_CurrentlySelected]->Down();
	UpdateSelected();
}

void svp::ButtonManagerComponent::UpdateSelected()
{
	for (size_t i{}, iSize{ m_pButtons.size() }; i < iSize; ++i)
	{
		if (m_pButtons[i]->GetState() == ButtonState::HIGHLIGHTED)
		{
			m_CurrentlySelected = int(i);
			break;
		}
	}
}

void svp::ButtonManagerComponent::Submit()
{
	m_pButtons[m_CurrentlySelected]->SetState(ButtonState::SELECTED);
}
