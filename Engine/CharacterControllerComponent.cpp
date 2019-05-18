#include "pch.h"
#include "CharacterControllerComponent.h"

svp::CharacterControllerComponent::CharacterControllerComponent(GameObject* const pGameObject)
	: BaseComponent(pGameObject)
{
	m_pInputComp = new InputComponent(pGameObject);
}


svp::CharacterControllerComponent::~CharacterControllerComponent()
{
	delete m_pInputComp;
}

void svp::CharacterControllerComponent::Update()
{
	m_pInputComp->Update();
}

void svp::CharacterControllerComponent::Render()
{
}

void svp::CharacterControllerComponent::SetButton(SDL_GameControllerButton button, InputCommands * pCommand)
{
	m_pInputComp->SetButton(button, pCommand);
}

void svp::CharacterControllerComponent::SetAxis(SDL_GameControllerAxis axis, InputCommands* pCommand)
{
	m_pInputComp->SetAxis(axis, pCommand);
}