#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int svp::Scene::idCounter = 0;

svp::Scene::Scene(const std::string& name)
	: m_Name{ name }
{
}

void svp::Scene::Add(GameObject * pObject)
{
	m_pGameObjects.push_back(pObject);
}

void svp::Scene::Initialize()
{
}

void svp::Scene::Update()
{
	if (m_pGameObjects.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update gameobjects, but there are none; in 'Scene::Update()'.");
		return;
	}

	//for (auto gameObject : m_pGameObjects)
	//{
	//	gameObject->Update();
	//}
}

void svp::Scene::Render() const
{
	if (m_pGameObjects.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to render gameobjects, but there are none; in 'Scene::Render()'.");
		return;
	}

	//for (const auto gameObject : m_pGameObjects)
	//{
	//	gameObject->Render();
	//}
}

void svp::Scene::FixedUpdate()
{
	if (m_pGameObjects.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update(fixed) gameobjects, but there are none; in 'Scene::FixedUpdate()'.");
		return;
	}

	//for (auto gameObject : m_pGameObjects)
	//{
	//	gameObject->FixedUpdate();
	//}
}
