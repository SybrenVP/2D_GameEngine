#include "pch.h"
#include "FygarLogic.h"
#include "GameTime.h"
#include "TriggerComponent.h"
#include "LayerFlags.h"
#include "../Game/DigDugHealthLogic.h"
#include "DigDugLogic.h"

digdug::FygarLogic::FygarLogic(svp::GameObject* const pGameObject, svp::GridComponent* pGrid, digdug::DigDugLogic* pDigDug)
	: BaseComponent(pGameObject)
	, m_IsAttacking{false}
	, m_pGrid{pGrid}
	, m_IsOnTarget{true}
	, m_MovePercentage{0.8f}
	, m_Scale{1}
	, m_pDigDug{pDigDug}
{
	m_Layer = LayerFlag::Trigger;
}


digdug::FygarLogic::~FygarLogic()
{
}

void digdug::FygarLogic::Update()
{
}

void digdug::FygarLogic::Render()
{
}

void digdug::FygarLogic::OnTriggerEnter(svp::TriggerComponent * pOther)
{
	if (auto digdugHealth = pOther->GetGameObject()->GetComponent<DigDugHealthLogic>())
	{
		digdugHealth->Damage(1);
	}
}

void digdug::FygarLogic::MoveRandom()
{
	if (m_Scale - 1.f <= 0.001f)
	{
		if (m_IsOnTarget && !m_IsAttacking)
		{
			ChooseState();
		}
		else if (!m_IsAttacking)
		{
			MoveToTarget();
		}
		else if (m_IsAttacking && svp::GameTime::GetInstance().IsTimerFinished(10))
		{
			m_IsAttacking = false;
		}
	}
	else
	{
		m_IsAttacking = false;
		m_IsGhost = false;
		//m_Scale += float(svp::GameTime::GetInstance().GetDeltaTime());
	}
}

void digdug::FygarLogic::SearchNewTargetWander()
{
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;
	bool topFound{ false }, botFound{ false }, leftFound{ false }, rightFound{ false };
	std::vector<svp::Transform*> pPossibleTargets{};
	auto pFreePoints = m_pGrid->GetFreePoints();
	int space = m_pGrid->GetSpace();

	for (auto point : pFreePoints)
	{
		if (!topFound)
		{
			if (abs(point->GetPosition().x - gameObjX) < 0.001f && abs((point->GetPosition().y + space) - gameObjY) < 0.001f)
			{
				pPossibleTargets.push_back(point);
				topFound = true;
				continue;
			}
		}
		if (!botFound)
		{
			if (abs(point->GetPosition().x - gameObjX) < 0.001f && abs((point->GetPosition().y - space) - gameObjY) < 0.001f)
			{
				pPossibleTargets.push_back(point);
				botFound = true;
				continue;
			}
		}
		if (!leftFound)
		{
			if (abs((point->GetPosition().x - space) - gameObjX) < 0.001f && abs(point->GetPosition().y - gameObjY) < 0.001f)
			{
				pPossibleTargets.push_back(point);
				leftFound = true;
				continue;
			}
		}
		if (!rightFound)
		{
			if (abs((point->GetPosition().x + space) - gameObjX) < 0.001f && abs(point->GetPosition().y - gameObjY) < 0.001f)
			{
				pPossibleTargets.push_back(point);
				rightFound = true;
				continue;
			}
		}
	}
	if (pPossibleTargets.size() > 0)
	{
		int randTarget = rand() % pPossibleTargets.size();
		m_TargetPoint = *pPossibleTargets[randTarget];
		m_IsOnTarget = false;
	}
}

void digdug::FygarLogic::SearchNewTargetGhost()
{
	int randPos = rand() % m_pGrid->GetFreePoints().size();
	m_TargetPoint.SetPosition(m_pGrid->GetFreePoints().at(randPos)->GetPosition().x, m_pGrid->GetFreePoints().at(randPos)->GetPosition().y, 0.f);
	m_IsOnTarget = false;
}

void digdug::FygarLogic::ChooseState()
{
	int randState = rand() % 6;
	switch (randState)
	{
	case 0:
		m_IsGhost = false;
		m_IsAttacking = true;
		break;
	case 1:
		m_IsGhost = true;
		SearchNewTargetGhost();
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		m_IsGhost = false;
		SearchNewTargetWander();
		break;
	}
}

void digdug::FygarLogic::MoveToTarget()
{
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;
	bool xOnTarget = false;
	bool yOnTarget = false;

	if (abs(m_TargetPoint.GetPosition().x - gameObjX) <= m_MovePercentage)
	{
		gameObjX = m_TargetPoint.GetPosition().x;
		xOnTarget = true;
	}
	else
	{
		gameObjX = gameObjX + Sign(m_TargetPoint.GetPosition().x - gameObjX) * m_MovePercentage;
	}
	
	if (abs(m_TargetPoint.GetPosition().y - gameObjY) <= m_MovePercentage)
	{
		gameObjY = m_TargetPoint.GetPosition().y;
		yOnTarget = true;
	}
	else
	{
		gameObjY = gameObjY + Sign(m_TargetPoint.GetPosition().y - gameObjY) * m_MovePercentage;
	}
	
	m_IsOnTarget = xOnTarget && yOnTarget;
	m_pGameObject->SetPosition(gameObjX, gameObjY);
}

float digdug::FygarLogic::Sign(float val)
{
	if (val < 0)
		return -1.f;
	else
		return 1.f;
}
