#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void svp::SceneManager::Initialize()
{
	if (m_pScenes.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to init scenes, but there are none; in 'SceneManager::Initialize()'.");
		return;
	}

	for (auto scene : m_pScenes)
	{
		scene->Initialize();
	}
}

void svp::SceneManager::Update()
{
	if (m_pScenes.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update scenes, but there are none; in 'SceneManager::Update()'.");
		return;
	}

	for (auto scene : m_pScenes)
	{
		scene->Update();
	}
}

void svp::SceneManager::FixedUpdate()
{
	for (auto scene : m_pScenes)
	{
		scene->FixedUpdate();
	}
}

void svp::SceneManager::Render()
{
	for (auto scene : m_pScenes)
	{
		scene->Render();
	}
}

svp::Scene& svp::SceneManager::CreateScene(const std::string& name)
{
	Scene* const pScene{ new Scene{name} };
	m_pScenes.push_back(pScene);

	return *pScene;
}

void svp::SceneManager::AddScene(Scene* pScene)
{
	for (auto scene : m_pScenes)
	{
		if (scene == pScene)
		{
			Logger::GetInstance().Log(Logger::LogType::Error, "Scene already exists; in 'SceneManager::AddScene()'.");
			return;
		}
	}

	m_pScenes.push_back(pScene);
}

svp::SceneManager::~SceneManager()
{
	for (size_t i{}; i < m_pScenes.size(); i++)
	{
		if (m_pScenes[i])
			delete m_pScenes[i];
	}
}
