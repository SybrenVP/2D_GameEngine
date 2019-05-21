#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

void svp::SceneManager::Initialize()
{
	if (m_pScenes.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to init scenes, but there are none; in 'SceneManager::Initialize()'.");
		return;
	}

	m_pScenes[m_ActiveScene]->Initialize();
}

void svp::SceneManager::Update()
{
	if (m_pScenes.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update scenes, but there are none; in 'SceneManager::Update()'.");
		return;
	}

	m_pScenes[m_ActiveScene]->Update();
}

void svp::SceneManager::FixedUpdate()
{
	m_pScenes[m_ActiveScene]->FixedUpdate();
}

void svp::SceneManager::Render()
{
	m_pScenes[m_ActiveScene]->Render();
}

void svp::SceneManager::SetActiveScene()
{
	delete m_pScenes[m_ActiveScene];
	m_pScenes[m_ActiveScene] = nullptr;

	for (size_t i{}, iSize{ m_SceneNames.size() }; i < iSize; ++i)
	{
		if (m_SceneNames[i] == m_ActiveScene)
		{
			m_SceneNames[i] = m_SceneNames[m_SceneNames.size() - 1];
			m_SceneNames.pop_back();
		}
	}
	
	//Reset Singletons
	InputManager::GetInstance().RemoveAllPlayers();

	m_ActiveScene = m_NewActiveScene;
	m_SwitchScene = false;
	Initialize();
}

svp::Scene& svp::SceneManager::CreateScene(const std::string& name)
{
	Scene* const pScene{ new Scene{name} };
	m_pScenes[name] = (pScene);
	m_SceneNames.push_back(name);

	return *pScene;
}

void svp::SceneManager::AddScene(Scene* pScene)
{
	if (m_pScenes[pScene->GetName()] == pScene)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Scene already exists; in 'SceneManager::AddScene()'.");
		return;
	}

	m_SceneNames.push_back(pScene->GetName());
	m_pScenes[pScene->GetName()] = pScene;
}

void svp::SceneManager::SwitchScene(std::string name)
{
	m_NewActiveScene = name;
	m_SwitchScene = true;
}

svp::SceneManager::~SceneManager()
{
	for (auto scene : m_pScenes)
	{
		if(scene.second)
			delete scene.second;
	}
	m_pScenes.clear();
}
