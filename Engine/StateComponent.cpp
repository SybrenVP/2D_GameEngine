#include "pch.h"
#include "StateComponent.h"
#include "State.h"
#include "SpriteComponent.h"
#include "../Game/DigDugStates.h"
#include "../Game/DigDugLogic.h"
#include "../Game/FygarState.h"
#include "../Game/FygarLogic.h"

svp::StateComponent::StateComponent(GameObject* const pGameObject, State* pCurrentState)
	: BaseComponent(pGameObject)
	, m_pCurrentState(pCurrentState)
{
	m_pCurrentState->SetSprite(m_pGameObject->GetComponent<SpriteComponent>());
	//if (reinterpret_cast<digdug::DigDugState*>(pCurrentState))
	//{
	//	digdug::DigDugState* pDigDugState = reinterpret_cast<digdug::DigDugState*>(pCurrentState);
	//	pDigDugState->SetDigDug(m_pGameObject->GetComponent<digdug::DigDugLogic>());
	//}
	//else if (reinterpret_cast<digdug::FygarState*>(pCurrentState))
	//{
	//	digdug::FygarState* pFygarState = reinterpret_cast<digdug::FygarState*>(pCurrentState);
	//	pFygarState->SetFygar(m_pGameObject->GetComponent<digdug::FygarLogic>());
	//}
	m_pCurrentState->Enter();
}


svp::StateComponent::~StateComponent()
{
	delete m_pCurrentState;
}

void svp::StateComponent::Update()
{
	if (m_pCurrentState->Update())
	{
		m_pCurrentState->Exit();
		
		auto temp = m_pCurrentState;
		m_pCurrentState = m_pCurrentState->GetTarget();
		delete temp;
		temp = nullptr;

		m_pCurrentState->Enter();
	}
}

