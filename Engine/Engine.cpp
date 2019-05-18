#include "pch.h"
#include "Engine.h"

#include <chrono>
#include <thread>
#include <windows.h>
#include <memory> 

#include <SDL.h>

#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "Achievements.h"

#include "Audio.h"
#include "AudioLocator.h"

//Scenes
#include "FPSScene.h"

void svp::Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "SDL_Init error; in 'Engine::Initialize()'.");
		throw std::runtime_error(std::string("SDL init error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow("2D_GameEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

	if (window == nullptr)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "SDL_CreateWindow error; in 'Engine::Initialize()'.");
		throw std::runtime_error(std::string("SDL_CreateWindow error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Initialize(window);
	InputManager::GetInstance().Initialize();
}

void svp::Engine::Load() const
{ //Load scenes here
	SceneManager::GetInstance().AddScene(new FPSScene());
	SceneManager::GetInstance().Initialize();
}

void svp::Engine::Run()
{
	Initialize();

	ResourceManager::GetInstance().Init("../Data/");

	Load();

	//Gameloop
	{
		InputManager& input = InputManager::GetInstance();
		Renderer& renderer = Renderer::GetInstance();
		GameTime& time = GameTime::GetInstance(); //GameTime singleton
		SceneManager& sceneManager = SceneManager::GetInstance(); //SceneManager singleton
		
		//Init achievements
		Achievements::GetInstance().Init();

		time.Initialize();
		while (input.IsNotQuitting())
		{
			time.Update();

			sceneManager.Update();

			while (time.IsLagging())
			{
				sceneManager.FixedUpdate(); //Needs to use GameTime::m_MsPerUpdate as time instead of deltaTime.
				time.UpdateLag();
			}

			renderer.Render();
		}
	}

	Cleanup();
}

void svp::Engine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	InputManager::GetInstance().CloseControllers();

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	
	SDL_Quit();
}
