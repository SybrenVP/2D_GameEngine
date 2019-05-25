#include "pch.h"
#include "CharacterControllerComponent.h"

svp::CharacterControllerComponent::CharacterControllerComponent(GameObject* const pGameObject, bool isKeyboard)
	: BaseComponent(pGameObject)
{
	m_pInputComp = new InputComponent(pGameObject, isKeyboard);
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

void svp::CharacterControllerComponent::SetButton(SDL_GameControllerButton button, InputCommands * pCommand, bool down)
{
	m_pInputComp->SetButton(button, pCommand, down);
}

void svp::CharacterControllerComponent::SetButton(SDL_Scancode key, InputCommands* pCommand, bool down)
{
	m_pInputComp->SetButton(key, pCommand, down);
}