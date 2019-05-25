#include "pch.h"
#include "MenuScene.h"

#include "GameObject.h"
#include "Components.h"

#include "Renderer.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Audio.h"
#include "AudioLocator.h"

//Own scripts

digdug::MenuScene::MenuScene()
	: Scene("MenuScene")
{
}


digdug::MenuScene::~MenuScene()
{
	for (auto gameObject : m_pGameObjects)
	{
		if (gameObject)
			delete gameObject;
	}
}

void digdug::MenuScene::Initialize()
{
	using namespace svp;

	//Buttons
	GameObject* const pOnePlayerButton = new GameObject();
	GameObject* const pTwoPlayerButton = new GameObject();
	pOnePlayerButton->SetPosition(150.f, 50.f);
	pTwoPlayerButton->SetPosition(150.f, 250.f);
	TextureComponent* pNormalOne = new TextureComponent(pOnePlayerButton, "ButtonOne/Button.png");
	TextureComponent* pHighlightedOne = new TextureComponent(pOnePlayerButton, "ButtonOne/HighLighted.png");
	TextureComponent* pSelectedOne = new TextureComponent(pOnePlayerButton, "ButtonOne/Selected.png");
	ButtonComponent* pOneButtonComp = new ButtonComponent(pOnePlayerButton, new digdug::OnePlayerCommand(),pNormalOne, pHighlightedOne, pSelectedOne);
	
	TextureComponent* pNormalTwo = new TextureComponent(pTwoPlayerButton, "ButtonTwo/Button.png");
	TextureComponent* pHighlightedTwo = new TextureComponent(pTwoPlayerButton, "ButtonTwo/HighLighted.png");
	TextureComponent* pSelectedTwo = new TextureComponent(pTwoPlayerButton, "ButtonTwo/Selected.png");
	ButtonComponent* pTwoButtonComp = new ButtonComponent(pTwoPlayerButton, new digdug::TwoPlayerCommand(), pNormalTwo, pHighlightedTwo, pSelectedTwo);
	
	pOneButtonComp->SetConnections(nullptr, nullptr, nullptr, pTwoButtonComp);
	pTwoButtonComp->SetConnections(nullptr, nullptr, pOneButtonComp, nullptr);
	
	pOnePlayerButton->AddComponent(pOneButtonComp);
	pTwoPlayerButton->AddComponent(pTwoButtonComp);
	Add(pOnePlayerButton);
	Add(pTwoPlayerButton);

	std::vector<ButtonComponent*> pButtons{};
	pButtons.push_back(pOneButtonComp);
	pButtons.push_back(pTwoButtonComp);

	//Player to control the menu
	GameObject* const pPlayer = new GameObject();
	InputComponent* pMenuInput = new InputComponent(pPlayer);
	pMenuInput->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, new ButtonLeftCommand());
	pMenuInput->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, new ButtonDownCommand());
	pMenuInput->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, new ButtonRightCommand());
	pMenuInput->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, new ButtonUpCommand());
	pMenuInput->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, new ButtonSubmit());
	pPlayer->AddComponent(pMenuInput);
	ButtonManagerComponent* pManager = new ButtonManagerComponent(pPlayer, pButtons);
	pPlayer->AddComponent(pManager);
	Add(pPlayer);
}

void digdug::MenuScene::Update()
{
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->Update();
	}
}

void digdug::MenuScene::Render() const
{
	for (const auto gameObject : m_pGameObjects)
		gameObject->Render();
}
