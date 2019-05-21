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
	, m_IsInTrigger{false}
	, m_OnLayer{ onLayer }
	, m_pCharacterGameObjects{ nullptr }
{
	m_pActiveScene = SceneManager::GetInstance().GetActiveScene();
	m_pCharacterGameObjects = InputManager::GetInstance().GetPlayersAsGameObjects();
}

void svp::TriggerComponent::Update()
{
	for (auto go : m_pCharacterGameObjects)
	{
		bool inside{false};
		if(go)
			inside = InsideTrigger(go->GetTransform());
		
		if (inside && !m_IsInTrigger)
		{
			TriggerEnter(go->GetComponent<TriggerComponent>());
		}
		else if (!inside && m_IsInTrigger)
		{
			TriggerLeave(go->GetComponent<TriggerComponent>());
		}
	}
}

void svp::TriggerComponent::Render()
{
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
			m_IsInTrigger = true;
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
			m_IsInTrigger = false;
		}
	}
}

bool svp::TriggerComponent::InsideTrigger(Transform pOther)
{
	float otherXPos{ pOther.GetPosition().x };
	float otherYPos{ pOther.GetPosition().y };
	float xLeft{this->GetGameObject()->GetTransform().GetPosition().x - m_Width / 2.f};
	float xRight{this->GetGameObject()->GetTransform().GetPosition().x + m_Width / 2.f};
	float yBot{this->GetGameObject()->GetTransform().GetPosition().y + m_Height / 2.f};
	float yTop{this->GetGameObject()->GetTransform().GetPosition().y - m_Height / 2.f};

	if (otherXPos > xLeft + m_XOffset && otherXPos < xRight + m_XOffset && otherYPos < yBot + m_YOffset && otherYPos > yTop + m_YOffset)
		return true;
	else
		return false;
}