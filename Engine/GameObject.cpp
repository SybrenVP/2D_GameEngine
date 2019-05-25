#include "pch.h"
#include "GameObject.h"
#include "BaseComponent.h"

void svp::GameObject::Update()
{
	if (m_pComponents.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update components, but there are none; in 'GameObject::Update()'.");
		return;
	}

	if (m_Active)
	{
		for (auto component : m_pComponents)
		{
			component->Update();
		}
	}
}

void svp::GameObject::FixedUpdate()
{
	if (m_pComponents.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to update(fixed) components, but there are none; in 'GameObject::FixedUpdate()'.");
		return;
	}

	if (m_Active)
	{
		for (auto component : m_pComponents)
		{
			component->FixedUpdate();
		}
	}
}

void svp::GameObject::Render() const
{
	if (m_pComponents.size() <= 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Trying to render components, but there are none; in 'GameObject::Render()'.");
		return;
	}

	if (m_Active)
	{
		for (auto component : m_pComponents)
		{
			component->Render();
		}
	}
}

void svp::GameObject::AddComponent(BaseComponent * pComponent)
{
	m_pComponents.push_back(pComponent);
}

void svp::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void svp::GameObject::Translate(float x, float y)
{
	m_Transform.SetPosition(m_Transform.GetPosition().x + x, m_Transform.GetPosition().y + y, m_Transform.GetPosition().z);
}

svp::GameObject::~GameObject()
{
	for (size_t i{}; i < m_pComponents.size(); i++)
	{
		if (m_pComponents[i])
			delete m_pComponents[i];
	}
}