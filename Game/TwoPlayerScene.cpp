#include "pch.h"
#include "TwoPlayerScene.h"

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
#include "../Game/TexFillGrid.h"
#include "../Game/RockLogic.h"
#include "../Game/DigDugHealthLogic.h"

digdug::TwoPlayerScene::TwoPlayerScene()
	: Scene("TwoPlayer")
{
}

digdug::TwoPlayerScene::~TwoPlayerScene()
{
	for (auto gameObject : m_pGameObjects)
	{
		if (gameObject)
			delete gameObject;
	}
}

void digdug::TwoPlayerScene::Initialize()
{
	using namespace svp;
	//Add the grid
	GameObject* pGrid = new GameObject();
	auto gridComp = new GridComponent(pGrid, 20, 20, 40);
	pGrid->AddComponent(gridComp);
	
	auto gridTex = new TextureComponent(pGrid, "Ground.png");
	auto gridTexFillComp = new TexFillGrid(pGrid, gridComp, gridTex);
	pGrid->AddComponent(gridTexFillComp);
	Add(pGrid);

	//Make a player, Make a charcontroller, add the input, add it to the player
	GameObject* const pDigDugTwo = new GameObject();
	auto charContCompTwo = new CharacterControllerComponent(pDigDugTwo, true);
	charContCompTwo->SetButton(SDL_SCANCODE_A, new GridMoveLeftCommand());
	charContCompTwo->SetButton(SDL_SCANCODE_S, new GridMoveDownCommand());
	charContCompTwo->SetButton(SDL_SCANCODE_D, new GridMoveRightCommand());
	charContCompTwo->SetButton(SDL_SCANCODE_W, new GridMoveUpCommand());
	charContCompTwo->SetButton(SDL_SCANCODE_E, new DigDugAttackCommand());
	charContCompTwo->SetButton(SDL_SCANCODE_E, new DigDugAttackStopCommand(), false);
	pDigDugTwo->AddComponent(charContCompTwo);

	//Make a graph movement component, add it to the player
	auto pGraphTwo = new GraphMovementComponent(pDigDugTwo, pGrid->GetComponent<GridComponent>(), 1);
	pDigDugTwo->AddComponent(pGraphTwo);

	//Make a sprite component, add it to the player
	auto pSpriteTwo = new SpriteComponent(pDigDugTwo);
	pSpriteTwo->AddTexture("Idle", "TempNormalDigDug.png");
	pSpriteTwo->AddTexture("Attack", "TempAttackDigDug.png");
	pSpriteTwo->AddTexture("Dead", "Grave.png");
	pDigDugTwo->AddComponent(pSpriteTwo);

	auto pSpriteAttackTwo = new SpriteComponent(pDigDugTwo);
	pSpriteAttackTwo->AddTexture("Pump0", "Pump/Pump0.png");
	pSpriteAttackTwo->AddTexture("Pump1", "Pump/Pump1.png");
	pSpriteAttackTwo->AddTexture("Pump2", "Pump/Pump2.png");
	pSpriteAttackTwo->AddTexture("Pump3", "Pump/Pump3.png");

	//Add the logic
	auto pDigDugLogicTwo = new digdug::DigDugLogic(pDigDugTwo, pSpriteAttackTwo);
	pDigDugTwo->AddComponent(pDigDugLogicTwo);

	//Add state component
	digdug::IdleState* pIdleStateTwo = new digdug::IdleState();
	auto pDigDugStatesTwo = new StateComponent(pDigDugTwo, pIdleStateTwo);
	pDigDugTwo->AddComponent(pDigDugStatesTwo);

	//Add triggerComponent
	TriggerComponent* pDigdugTrigger = new TriggerComponent(pDigDugTwo, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pDigDugTwo->AddComponent(pDigdugTrigger);

	//Add health
	TextureComponent* pHealthTex = new TextureComponent(pDigDugTwo, "Heart.png");
	Transform* pHealthPos = new Transform(10.f, 480.f - pHealthTex->GetHeight() - 10.f);
	DigDugHealthLogic* pDigDugHealth = new DigDugHealthLogic(pDigDugTwo, 4, pHealthTex, pHealthPos);
	pDigDugTwo->AddComponent(pDigDugHealth);

	//Add the player
	//Move the player
	pDigDugTwo->SetPosition(80, 40);
	Add(pDigDugTwo);

	//Make a player, Make a charcontroller, add the input, add it to the player
	GameObject* const pDigDug = new GameObject();
	auto charContComp = new CharacterControllerComponent(pDigDug);
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, new GridMoveDownCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, new GridMoveRightCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, new GridMoveUpCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, new DigDugAttackCommand());
	pDigDug->AddComponent(charContComp);

	//Make a graph movement component, add it to the player
	auto pGraph = new GraphMovementComponent(pDigDug, pGrid->GetComponent<GridComponent>(), 1);
	pDigDug->AddComponent(pGraph);

	//Make a sprite component, add it to the player
	auto pSprite = new SpriteComponent(pDigDug);
	pSprite->AddTexture("Idle", "TempNormalDigDug.png");
	pSprite->AddTexture("Attack", "TempAttackDigDug.png");
	pDigDug->AddComponent(pSprite);

	auto pSpriteAttack = new SpriteComponent(pDigDug);
	pSpriteAttack->AddTexture("Pump0", "Pump/Pump0.png");
	pSpriteAttack->AddTexture("Pump1", "Pump/Pump1.png");
	pSpriteAttack->AddTexture("Pump2", "Pump/Pump2.png");
	pSpriteAttack->AddTexture("Pump3", "Pump/Pump3.png");

	//Add the logic
	auto pDigDugLogic = new digdug::DigDugLogic(pDigDug, pSpriteAttack);
	pDigDug->AddComponent(pDigDugLogic);

	//Add state component
	digdug::IdleState* pIdleState = new digdug::IdleState();
	auto pDigDugStates = new StateComponent(pDigDug, pIdleState);
	pDigDug->AddComponent(pDigDugStates);

	//Move player and Add the player
	pDigDug->SetPosition(40, 40);
	Add(pDigDug);

	//Rock
	GameObject* const pRock = new GameObject();
	RockLogic* pRockLogic = new RockLogic(pRock, gridComp, *gridComp->GetPoints()[gridComp->GetHeight() * 3 + 5]);
	pRock->AddComponent(pRockLogic);
	TextureComponent* pRockTex = new TextureComponent(pRock, "Rock.png");
	pRock->AddComponent(pRockTex);
	TriggerComponent* pRockTrigger = new TriggerComponent(pRock, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pRock->AddComponent(pRockTrigger);
	Add(pRock);

	//FPS object
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsObject = new GameObject();
	const SDL_Color& fpsTextColor = { 255, 0, 0 };
	auto fpsComp = new FPSComponent(fpsObject, font, fpsTextColor);
	fpsComp->SetPosition(10.f, 10.f);
	fpsObject->AddComponent(fpsComp);
	Add(fpsObject);
}

void digdug::TwoPlayerScene::Update()
{
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->Update();
	}
}

void digdug::TwoPlayerScene::Render() const
{
	for (const auto gameObject : m_pGameObjects)
		gameObject->Render();
}
