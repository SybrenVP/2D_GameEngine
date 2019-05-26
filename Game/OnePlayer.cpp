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
#include "GridLoader.h"

//own scripts
#include "../Game/TriggerTestScript.h"
#include "../Game/DigDugLogic.h"
#include "../Game/DigDugStates.h"
#include "../Game/TexFillGrid.h"
#include "../Game/RockLogic.h"
#include "../Game/DigDugHealthLogic.h"
#include "../Game/FygarLogic.h"
#include "../Game/FygarState.h"
#include "../Game/GameManager.h"

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
	GameObject* const pDigDug = new GameObject();
	auto charContComp = new CharacterControllerComponent(pDigDug, true);
	charContComp->SetButton(SDL_SCANCODE_A, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_SCANCODE_S, new GridMoveDownCommand());
	charContComp->SetButton(SDL_SCANCODE_D, new GridMoveRightCommand());
	charContComp->SetButton(SDL_SCANCODE_W, new GridMoveUpCommand());
	charContComp->SetButton(SDL_SCANCODE_E, new DigDugAttackCommand());
	charContComp->SetButton(SDL_SCANCODE_E, new DigDugAttackStopCommand(), false);

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

	auto pAttackSprite = new SpriteComponent(pDigDug);
	pAttackSprite->AddTexture("Pump0", "Pump/Pump0.png");
	pAttackSprite->AddTexture("Pump1", "Pump/Pump1.png");
	pAttackSprite->AddTexture("Pump2", "Pump/Pump2.png");
	pAttackSprite->AddTexture("Pump3", "Pump/Pump3.png");

	//Add triggerComponent
	TriggerComponent* pDigdugTrigger = new TriggerComponent(pDigDug, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	pDigDug->AddComponent(pDigdugTrigger);

	//Add attack trigger
	TriggerComponent* pAttackTrigger = new TriggerComponent(pDigDug, float(gridComp->GetSpace() / 2.f), float(gridComp->GetSpace() / 2.f), 0.f, 0.f, LayerFlag::DigDugAttack);

	//Add the logic
	auto pDigDugLogic = new digdug::DigDugLogic(pDigDug, pAttackSprite, pAttackTrigger);
	pDigDug->AddComponent(pDigDugLogic);

	//Add state component
	digdug::IdleState* pIdleState = new digdug::IdleState();
	pIdleState->SetDigDug(pDigDugLogic);
	auto pDigDugStates = new StateComponent(pDigDug, pIdleState);
	pDigDug->AddComponent(pDigDugStates);

	//Add health
	TextureComponent* pHealthTex = new TextureComponent(pDigDug, "Heart.png");
	Transform* pHealthPos = new Transform(30.f, 670.f - pHealthTex->GetHeight() - 5.f);
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

	////Add Fygar
	//auto pFygarTwo = new GameObject();
	//FygarLogic* pFygarTwoLogic = new FygarLogic(pFygarTwo, gridComp, pDigDugLogic);
	//pFygarTwo->AddComponent(pFygarTwoLogic);
	//
	////Fygar sprite
	//auto pFygarTwoSpriteComp = new SpriteComponent(pFygarTwo);
	//pFygarTwoSpriteComp->AddTexture("Fygar", "FygarNormal.png");
	//pFygarTwoSpriteComp->AddTexture("GhostFygar", "FygarGhost.png");
	//pFygarTwoSpriteComp->AddTexture("FygarAttack", "FygarAttack.png");
	//pFygarTwoSpriteComp->AddTexture("FygarAttackFull", "FygarAttackFull.png");
	//pFygarTwo->AddComponent(pFygarTwoSpriteComp);
	//
	////Fygar state machine
	//digdug::WanderState* pWanderStateTwo = new digdug::WanderState();
	//pWanderStateTwo->SetFygar(pFygarTwoLogic);
	//auto pFygarTwoStates = new StateComponent(pFygarTwo, pWanderStateTwo);
	//pFygarTwo->AddComponent(pFygarTwoStates);
	//
	////Fygar trigger
	//TriggerComponent* pFygarTwoTrigger = new TriggerComponent(pFygarTwo, float(gridComp->GetSpace()), float(gridComp->GetSpace()));
	//pFygarTwo->AddComponent(pFygarTwoTrigger);
	//
	////Move and add Fygar
	//pFygarTwo->SetPosition(640.f, 360.f);
	//Add(pFygarTwo);
	//pMan->AddEnemy(pFygarTwo);

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
