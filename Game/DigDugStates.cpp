#include "pch.h"
#include "DigDugStates.h"
#include "SpriteComponent.h"
#include "DigDugLogic.h"
#include "GameTime.h"

#pragma region attackState
void digdug::AttackState::Enter()
{
	m_pSubjectSprite->SetTexture("Attack");
	m_pDigDug->SetAttackState(1);
	svp::GameTime::GetInstance().SetTimer(500, 3); //Set timer for the stages of attack
}

bool digdug::AttackState::Update()
{
	if (!m_pDigDug->IsAttacking())
	{
		IdleState* idle = new IdleState();
		idle->SetSprite(m_pSubjectSprite);
		idle->SetDigDug(m_pDigDug);
		
		delete m_pTargetState;
		m_pTargetState = nullptr;
		
		m_pTargetState = idle;
		return true;
	}

	if (m_pDigDug->IsDead())
	{
		DeadState* dead = new DeadState();
		dead->SetSprite(m_pSubjectSprite);
		dead->SetDigDug(m_pDigDug);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = dead;
		return true;
	}
	
	if (svp::GameTime::GetInstance().IsTimerFinished(3))
	{
		m_pDigDug->SetAttackState(2);

		svp::GameTime::GetInstance().SetTimer(500, 4);
		svp::GameTime::GetInstance().RemoveTimer(3);
	}
	else if (svp::GameTime::GetInstance().IsTimerFinished(4))
	{
		m_pDigDug->SetAttackState(3);
	}
	return false;
}

void digdug::AttackState::Exit()
{
	svp::GameTime::GetInstance().RemoveTimer(4);
	m_pDigDug->SetAttackState(0);
}
#pragma endregion

#pragma region idleState
void digdug::IdleState::Enter()
{
	m_pSubjectSprite->SetTexture("Idle");
}

bool digdug::IdleState::Update()
{
	if (m_pDigDug->IsAttacking())
	{
		AttackState* attack = new AttackState();
		attack->SetSprite(m_pSubjectSprite);
		attack->SetDigDug(m_pDigDug);
		
		delete m_pTargetState;
		m_pTargetState = nullptr;
		
		m_pTargetState = attack;
		return true;
	}

	if (m_pDigDug->IsDead())
	{
		DeadState* dead = new DeadState();
		dead->SetSprite(m_pSubjectSprite);
		dead->SetDigDug(m_pDigDug);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = dead;
		return true;
	}
	return false;
}

void digdug::IdleState::Exit()
{

}
#pragma endregion

#pragma region deadState
void digdug::DeadState::Enter()
{
	m_pSubjectSprite->SetTexture("Dead");
	svp::GameTime::GetInstance().SetTimer(2000, 2);
}

bool digdug::DeadState::Update()
{
	if (svp::GameTime::GetInstance().IsTimerFinished(2))
	{
		IdleState* idle = new IdleState();
		idle->SetSprite(m_pSubjectSprite);
		idle->SetDigDug(m_pDigDug);

		delete m_pTargetState;
		m_pTargetState = nullptr;

		m_pTargetState = idle;
		return true;
	}
	return false;
}

void digdug::DeadState::Exit()
{
	svp::GameTime::GetInstance().RemoveTimer(2);
}
#pragma endregion