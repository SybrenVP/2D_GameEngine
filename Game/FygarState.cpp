#include "pch.h"
#include "FygarState.h"
#include "../Game/FygarLogic.h"
#include "GameTime.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "TriggerComponent.h"

void digdug::FygarAttackState::Enter()
{
	svp::GameTime::GetInstance().SetTimer(2000, 5);
	m_pSubjectSprite->SetTexture("FygarAttack");
}

bool digdug::FygarAttackState::Update()
{
	if (svp::GameTime::GetInstance().IsTimerFinished(5))
	{
		if (!m_pFygar->m_SetAttackScale)
		{
			m_pFygar->GetGameObject()->GetComponent<svp::TriggerComponent>()->ScaleWidth(3);
			m_pFygar->m_SetAttackScale = true;
			m_pSubjectSprite->SetTexture("FygarAttackFull");
			svp::GameTime::GetInstance().SetTimer(1000, 10);
		}
		if (svp::GameTime::GetInstance().IsTimerFinished(10) && !m_pFygar->IsAttacking())
		{
			WanderState* wander = new WanderState();
			wander->SetSprite(m_pSubjectSprite);
			wander->SetFygar(m_pFygar);

			delete m_pTargetState;
			m_pTargetState = nullptr;

			m_pTargetState = wander;
			return true;
		}

		m_pFygar->MoveRandom();
	}
	return false;
}

void digdug::FygarAttackState::Exit()
{
	svp::GameTime::GetInstance().RemoveTimer(5);
	svp::GameTime::GetInstance().RemoveTimer(10);
	m_pFygar->m_SetAttackScale = false;
	m_pFygar->GetGameObject()->GetComponent<svp::TriggerComponent>()->ScaleWidth(1.f/3.f);
}

void digdug::WanderState::Enter()
{
	m_pSubjectSprite->SetTexture("Fygar");
}

bool digdug::WanderState::Update()
{
	if (m_pFygar->IsGhost())
	{
		GhostState* ghost = new GhostState();
		ghost->SetSprite(m_pSubjectSprite);
		ghost->SetFygar(m_pFygar);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = ghost;
		return true;
	}

	if (m_pFygar->IsAttacking())
	{
		FygarAttackState* attack = new FygarAttackState();
		attack->SetSprite(m_pSubjectSprite);
		attack->SetFygar(m_pFygar);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = attack;
		return true;
	}

	if (m_pFygar->GetScale() > 1.f)
	{
		BlowState* blow = new BlowState();
		blow->SetSprite(m_pSubjectSprite);
		blow->SetFygar(m_pFygar);
		
		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = blow;
		return true;
	}

	m_pFygar->MoveRandom();

	return false;
}

void digdug::WanderState::Exit()
{
}

void digdug::GhostState::Enter()
{
	m_pSubjectSprite->SetTexture("GhostFygar");
}

bool digdug::GhostState::Update()
{
	if (!m_pFygar->IsGhost())
	{
		WanderState* wander = new WanderState();
		wander->SetSprite(m_pSubjectSprite);
		wander->SetFygar(m_pFygar);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = wander;
		return true;
	}

	m_pFygar->MoveRandom();

	return false;
}

void digdug::GhostState::Exit()
{
}

void digdug::BlowState::Enter()
{
}

bool digdug::BlowState::Update()
{
	m_pSubjectSprite->GetTexture()->SetUniformScale(m_pFygar->GetScale());
	
	if (m_pFygar->GetScale() >= 1.5f)
	{
		WanderState* wander = new WanderState();
		wander->SetSprite(m_pSubjectSprite);
		wander->SetFygar(m_pFygar);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = wander;
		m_pFygar->GetGameObject()->SetActive(false);
		return true;
	}
	else if (m_pFygar->GetScale() - 1.f < 0.001f)
	{
		WanderState* wander = new WanderState();
		wander->SetSprite(m_pSubjectSprite);
		wander->SetFygar(m_pFygar);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = wander;
		return true;
	}
	else
	{
		m_pFygar->SetScale(m_pFygar->GetScale() + float(svp::GameTime::GetInstance().GetDeltaTime() / 2.f));
	}

	return false;
}

void digdug::BlowState::Exit()
{
}
