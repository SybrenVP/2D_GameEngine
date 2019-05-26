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
#include "GridLoader.h"

//own scripts
#include "../Game/TriggerTestScript.h"
#include "../Game/DigDugLogic.h"
#include "../Game/DigDugStates.h"
#include "../Game/TexFillGrid.h"
#include "../Game/RockLogic.h"
#include "../Game/DigDugHealthLogic.h"
#include "../Game/GameManager.h"
#include "../Game/FygarLogic.h"
#include "../Game/FygarState.h"

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
	//Add GameManager
	GameObject* pManager = new GameObject();
	GameManager* pMan = new GameManager(pManager);
	pManager->AddComponent(pMan);

	//Add bg
	GameObject* pBG = new GameObject();
	auto pBGTex = new TextureComponent(pBG, "background.png");
	pBGTex->SetOffset(0.f, 0.f);
	pBG->AddComponent(pBGTex);
	Add(pBG);

	//Add the grid
	GameObject* pGrid = new GameObject();
	auto gridComp = new GridComponent(pGrid, 20, 15, 40);
	pGrid->AddComponent(gridComp);
	
	GridLoader pLoader{ gridComp, "../Data/level1.txt" };
	pLoader.Open();
	pLoader.ReadPoints();

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

	//Add triggerComponent
	TriggerComponent* pDigdugTwoTrigger = new TriggerComponent(pDigDugTwo, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pDigDugTwo->AddComponent(pDigdugTwoTrigger);

	//Add attack trigger
	TriggerComponent* pAttackTriggerTwo = new TriggerComponent(pDigDugTwo, float(gridComp->GetSpace() / 2.f), float(gridComp->GetSpace() / 2.f));
	
	//Add the logic
	auto pDigDugLogicTwo = new digdug::DigDugLogic(pDigDugTwo, pSpriteAttackTwo, pAttackTriggerTwo);
	pDigDugTwo->AddComponent(pDigDugLogicTwo);

	//Add state component
	digdug::IdleState* pIdleStateTwo = new digdug::IdleState();
	pIdleStateTwo->SetDigDug(pDigDugLogicTwo);
	auto pDigDugStatesTwo = new StateComponent(pDigDugTwo, pIdleStateTwo);
	pDigDugTwo->AddComponent(pDigDugStatesTwo);
	
	//Add health
	TextureComponent* pHealthTexTwo = new TextureComponent(pDigDugTwo, "Heart.png");
	Transform* pHealthPosTwo = new Transform(30.f, 670.f - pHealthTexTwo->GetHeight() - 5.f);
	DigDugHealthLogic* pDigDugTwoHealth = new DigDugHealthLogic(pDigDugTwo, 4, pHealthTexTwo, pHealthPosTwo);
	pDigDugTwo->AddComponent(pDigDugTwoHealth);

	//Add the player
	//Move the player
	pDigDugTwo->SetPosition(400.f, 40.f);
	Add(pDigDugTwo);
	pMan->AddPlayer(pDigDugTwo);

	//Make a player, Make a charcontroller, add the input, add it to the player
	GameObject* const pDigDug = new GameObject();
	auto charContComp = new CharacterControllerComponent(pDigDug);
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, new GridMoveDownCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, new GridMoveRightCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, new GridMoveUpCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, new DigDugAttackCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, new DigDugAttackStopCommand(), false);
	pDigDug->AddComponent(charContComp);

	//Make a graph movement component, add it to the player
	auto pGraph = new GraphMovementComponent(pDigDug, pGrid->GetComponent<GridComponent>(), 1);
	pDigDug->AddComponent(pGraph);

	//Make a sprite component, add it to the player
	auto pSprite = new SpriteComponent(pDigDug);
	pSprite->AddTexture("Idle", "TempNormalDigDug.png");
	pSprite->AddTexture("Attack", "TempAttackDigDug.png");
	pSprite->AddTexture("Dead", "Grave.png");
	pDigDug->AddComponent(pSprite);

	auto pSpriteAttack = new SpriteComponent(pDigDug);
	pSpriteAttack->AddTexture("Pump0", "Pump/Pump0.png");
	pSpriteAttack->AddTexture("Pump1", "Pump/Pump1.png");
	pSpriteAttack->AddTexture("Pump2", "Pump/Pump2.png");
	pSpriteAttack->AddTexture("Pump3", "Pump/Pump3.png");

	//Add triggerComponent
	TriggerComponent* pDigdugTrigger = new TriggerComponent(pDigDug, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pDigDug->AddComponent(pDigdugTrigger);
	
	//Add attack trigger
	TriggerComponent* pAttackTrigger = new TriggerComponent(pDigDug, float(gridComp->GetSpace() / 2.f), float(gridComp->GetSpace() / 2.f));
	
	//Add the logic
	auto pDigDugLogic = new digdug::DigDugLogic(pDigDug, pSpriteAttack, pAttackTrigger);
	pDigDug->AddComponent(pDigDugLogic);

	//Add state component
	digdug::IdleState* pIdleState = new digdug::IdleState();
	pIdleState->SetDigDug(pDigDugLogic);
	auto pDigDugStates = new StateComponent(pDigDug, pIdleState);
	pDigDug->AddComponent(pDigDugStates);

	//Add health
	TextureComponent* pHealthTex = new TextureComponent(pDigDug, "Heart.png");
	Transform* pHealthPos = new Transform(400.f, 670.f - pHealthTex->GetHeight() - 5.f);
	DigDugHealthLogic* pDigDugHealth = new DigDugHealthLogic(pDigDug, 4, pHealthTex, pHealthPos);
	pDigDug->AddComponent(pDigDugHealth);

	//Move player and Add the player
	pDigDug->SetPosition(400.f, 40.f);
	Add(pDigDug);
	pMan->AddPlayer(pDigDug);

	//Add Fygar
	auto pFygar = new GameObject();
	FygarLogic* pFygarLogic = new FygarLogic(pFygar, gridComp, pDigDugLogic);
	pFygar->AddComponent(pFygarLogic);

	//Fygar sprite
	auto pFygarSpriteComp = new SpriteComponent(pFygar);
	pFygarSpriteComp->AddTexture("Fygar", "FygarNormal.png");
	pFygarSpriteComp->AddTexture("GhostFygar", "FygarGhost.png");
	pFygarSpriteComp->AddTexture("FygarAttack", "FygarAttack.png");
	pFygarSpriteComp->AddTexture("FygarAttackFull", "FygarAttackFull.png");
	pFygar->AddComponent(pFygarSpriteComp);

	//Fygar state machine
	digdug::WanderState* pWanderState = new digdug::WanderState();
	pWanderState->SetFygar(pFygarLogic);
	auto pFygarStates = new StateComponent(pFygar, pWanderState);
	pFygar->AddComponent(pFygarStates);

	//Fygar trigger
	TriggerComponent* pFygarTrigger = new TriggerComponent(pFygar, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pFygar->AddComponent(pFygarTrigger);

	//Move and add Fygar
	pFygar->SetPosition(160.f, 360.f);
	Add(pFygar);
	pMan->AddEnemy(pFygar);

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

	Add(pManager);

	ConsoleAudio* audio = new ConsoleAudio();
	AudioLocator::Provide(audio);
	Audio& mainTheme = AudioLocator::GetAudio();
	mainTheme.PlayMusic(0);
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
