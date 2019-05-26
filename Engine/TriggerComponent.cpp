#include "pch.h"
#include "TriggerComponent.h"
#include "Components.h"
#include "SceneManager.h"
#include "Scene.h"

svp::TriggerComponent::TriggerComponent(GameObject * const pGameObject, float width, float height, float xOffset, float yOffset, LayerFlag onLayer)
	: BaseComponent(pGameObject)
	, m_Width{ width }
	, m_Height{ height }
	, m_XOffset{ xOffset }
	, m_YOffset{ yOffset }
	, m_OnLayer{ onLayer }
	, m_pCharacterGameObjects{ nullptr }
	, m_Active{true}
{
	m_pActiveScene = SceneManager::GetInstance().GetActiveScene();
	m_pCharacterGameObjects = InputManager::GetInstance().GetPlayersAsGameObjects();

	for (auto go : m_pCharacterGameObjects)
		m_pIsInTrigger[go] = false;
}

void svp::TriggerComponent::Update()
{
	for (auto go : SceneManager::GetInstance().GetActiveScene()->GetGameObjects())
	{
		auto triggers = go->GetComponents<TriggerComponent>();
		for(auto trigger : triggers)
		{
			bool inside{ false };
			if (go)
				inside = InsideTrigger(go->GetTransform());
			if (trigger->m_Active)
			{
				if (inside && !m_pIsInTrigger[go])
				{
					TriggerEnter(trigger);
				}
			}
			if (!inside && m_pIsInTrigger[go])
			{
				TriggerLeave(trigger);
			}
		}
	}

	if(!m_Active)
	{
		m_XOffset = 0.0f;
		m_YOffset = 0.0f;
	}
}

void svp::TriggerComponent::Render()
{
#ifdef DEBUG
	if (m_Active)
	{
		SDL_Rect rect{};
		rect.x = int(m_pGameObject->GetTransform().GetPosition().x - m_Width / 2.f + m_XOffset);
		rect.y = int(m_pGameObject->GetTransform().GetPosition().y - m_Height / 2.f + m_YOffset);
		rect.w = int(m_Width);
		rect.h = int(m_Height);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}
#endif
}

void svp::TriggerComponent::FixedUpdate()
{
}

void svp::TriggerComponent::TriggerEnter(TriggerComponent* pOther)
{
	auto components = m_pGameObject->GetAllComponents();
	for (auto comp : components)
	{
		if (comp->GetLayerFlags() == m_OnLayer)
		{
			Logger::GetInstance().Log(Logger::LogType::Debug, "Trigger Enter in TriggerComponent");
			comp->OnTriggerEnter(pOther);
			m_pIsInTrigger[pOther->GetGameObject()] = true;
		}
	}
}

void svp::TriggerComponent::TriggerLeave(TriggerComponent * pOther)
{
	auto components = m_pGameObject->GetAllComponents();
	for (auto comp : components)
	{
		if (comp->GetLayerFlags() == m_OnLayer)
		{
			Logger::GetInstance().Log(Logger::LogType::Debug, "Trigger Leave in TriggerComponent");
			comp->OnTriggerLeave(pOther);
			m_pIsInTrigger[pOther->GetGameObject()] = false;
		}
	}
}

bool svp::TriggerComponent::InsideTrigger(Transform pOther)
{
	float otherXPos{ pOther.GetPosition().x };
	float otherYPos{ pOther.GetPosition().y };

	float xLeft{m_pGameObject->GetTransform().GetPosition().x - m_Width / 2.f};
	float xRight{m_pGameObject->GetTransform().GetPosition().x + m_Width / 2.f};

	float yBot{m_pGameObject->GetTransform().GetPosition().y + m_Height / 2.f};
	float yTop{m_pGameObject->GetTransform().GetPosition().y - m_Height / 2.f};

	if (otherXPos > xLeft + m_XOffset && otherXPos < xRight + m_XOffset && otherYPos < yBot + m_YOffset && otherYPos > yTop + m_YOffset)
		return true;
	else
		return false;
}