#include "pch.h"
#include "FPSScene.h"

#include "GameObject.h"
#include "Components.h"

#include "Renderer.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Audio.h"
#include "AudioLocator.h"

svp::FPSScene::FPSScene()
	: Scene("FPSScene")
{
}


svp::FPSScene::~FPSScene()
{
	for (auto gameObject : m_pGameObjects)
	{

		if (gameObject)
			delete gameObject;
	}
}

void svp::FPSScene::Initialize()
{
	//Add the grid
	GameObject* pGrid = new GameObject();
	auto gridComp = new GridComponent(pGrid, 20, 20, 40);
	pGrid->AddComponent(gridComp);
	Add(pGrid);

	//Make a player, Make a charcontroller, add the input, add it to the player
	GameObject* const pPlayer = new GameObject();
	auto charContComp = new CharacterControllerComponent(pPlayer);
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, new GridMoveLeftCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, new GridMoveDownCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, new GridMoveRightCommand());
	charContComp->SetButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, new GridMoveUpCommand());
	pPlayer->AddComponent(charContComp);

	//Make a graph movement component, add it to the player
	auto pGraph = new GraphMovementComponent(pPlayer, pGrid->GetComponent<GridComponent>());
	pPlayer->AddComponent(pGraph);

	//Make a texture (needs to be a sprite comp), add it to the player
	auto pTexture = new TextureComponent(pPlayer, "TempPlayer.png");
	pPlayer->AddComponent(pTexture);

	//Move player and Add the player
	pPlayer->SetPosition(40, 40);
	Add(pPlayer);

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

void svp::FPSScene::Update()
{
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->Update();
	}
}

void svp::FPSScene::Render() const
{
	for (const auto gameObject : m_pGameObjects)
		gameObject->Render();
}