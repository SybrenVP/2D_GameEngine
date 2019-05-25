#include "pch.h"
#include "OnePlayer.h"

#include "GameObject.h"
#include "Components.h"

#include "Renderer.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Audio.h"
#include "AudioLocator.h"

//own scripts
#include "../Game/TriggerTestScript.h"
#include "../Game/DigDugLogic.h"
#include "../Game/DigDugStates.h"

digdug::OnePlayer::OnePlayer()
	: Scene("OnePlayer")
{
}

digdug::OnePlayer::~OnePlayer()
{
	for (auto gameObject : m_pGameObjects)
	{
		if (gameObject)
			delete gameObject;
	}
}

void digdug::OnePlayer::Initialize()
{
	using namespace svp;
	//Add the grid
	GameObject* pGrid = new GameObject();
	auto gridComp = new GridComponent(pGrid, 20, 20, 40);
	pGrid->AddComponent(gridComp);
	Add(pGrid);

	//Trigger test object
	GameObject* const pTrigger = new GameObject();
	auto triggerSpace = new TextureComponent(pTrigger, "TempIdlePlayer.png");
	pTrigger->AddComponent(triggerSpace);
	auto triggerComp = new TriggerComponent(pTrigger, 10.f, 10.f, 0.f, 0.f, LayerFlag::Trigger);
	pTrigger->AddComponent(triggerComp);
	pTrigger->SetPosition(80, 80);
	auto ownScript = new TriggerTestScript(pTrigger);
	pTrigger->AddComponent(ownScript);
	Add(pTrigger);

	//Make a player, Make a charcontroller, add the input, add it to the player
	GameObject* const pDigDug = new GameObject();
	auto charContComp = new CharacterControllerComponent(pDigDug);
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, new GridMoveDownCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, new GridMoveRightCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, new GridMoveUpCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, new DigDugAttackCommand(), false);
	charContComp->SetButton(SDL_SCANCODE_A, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_SCANCODE_S, new GridMoveDownCommand());
	charContComp->SetButton(SDL_SCANCODE_D, new GridMoveRightCommand());
	charContComp->SetButton(SDL_SCANCODE_W, new GridMoveUpCommand());
	pDigDug->AddComponent(charContComp);

	//Make a graph movement component, add it to the player
	auto pGraph = new GraphMovementComponent(pDigDug, pGrid->GetComponent<GridComponent>(), 1);
	pDigDug->AddComponent(pGraph);

	//Make a sprite component, add it to the player
	auto pSprite = new SpriteComponent(pDigDug);
	pSprite->AddTexture("Idle", "TempIdlePlayer.png");
	pSprite->AddTexture("Attack", "TempAttackPlayer.png");
	pDigDug->AddComponent(pSprite);

	auto pAttackSprite = new SpriteComponent(pDigDug);
	pAttackSprite->AddTexture("Pump1", "Pump/Pump1.png");
	pAttackSprite->AddTexture("Pump2", "Pump/Pump2.png");
	pAttackSprite->AddTexture("Pump3", "Pump/Pump3.png");

	//Add the logic
	auto pDigDugLogic = new digdug::DigDugLogic(pDigDug, pAttackSprite);
	pDigDug->AddComponent(pDigDugLogic);

	//Add state component
	digdug::IdleState* pIdleState = new digdug::IdleState();
	auto pDigDugStates = new StateComponent(pDigDug, pIdleState);
	pDigDug->AddComponent(pDigDugStates);

	//Move player and Add the player
	pDigDug->SetPosition(40, 40);
	Add(pDigDug);

	//FPS object
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsObject = new GameObject();
	const SDL_Color& fpsTextColor = { 255, 0, 0 };
	auto fpsComp = new FPSComponent(fpsObject, font, fpsTextColor);
	fpsComp->SetPosition(10.f, 10.f);
	fpsObject->AddComponent(fpsComp);
	Add(fpsObject);

	//Audio
	ConsoleAudio* audio = new ConsoleAudio();
	AudioLocator::Provide(audio);
	Audio& mainTheme = AudioLocator::GetAudio();
	mainTheme.PlayMusic(0);
}

void digdug::OnePlayer::Update()
{
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->Update();
	}
}

void digdug::OnePlayer::Render() const
{
	for (const auto gameObject : m_pGameObjects)
		gameObject->Render();
}
