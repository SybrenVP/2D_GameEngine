#include "pch.h"
#include "DigDugLogic.h"
#include "GameTime.h"
#include "TriggerComponent.h"
#include "FygarLogic.h"

digdug::DigDugLogic::DigDugLogic(svp::GameObject* const pGameObject, svp::SpriteComponent* pAttackSprite, svp::TriggerComponent* pAttackTrigger)
	: BaseComponent(pGameObject)
	, m_Attacking{false}
	, m_IsDead{false}
	, m_DirOfAttack{0.f}
	, m_AttackStage{0}
	, m_pAttackSprite{ pAttackSprite }
	, m_pAttackTrigger{ pAttackTrigger }
{
	m_BeginPos = { 400.f, 80.f };
	m_pAttackSprite->SetTexture("Pump0");
	m_Layer = LayerFlag::DigDugAttack;
}


digdug::DigDugLogic::~DigDugLogic()
{
	delete m_pAttackSprite;
	delete m_pAttackTrigger;
}

void digdug::DigDugLogic::Update()
{
	if (m_IsDead)
	{
		m_pAttackTrigger->SetOffset(1000.f, 1000.f);
		m_pGameObject->GetComponent<svp::GraphMovementComponent>()->SetMovement(false);
		if (svp::GameTime::GetInstance().IsTimerFinished(2))
		{
			m_pGameObject->GetComponent<svp::GraphMovementComponent>()->SetMovement(true);
			m_pGameObject->SetPosition(m_BeginPos.GetPosition().x, m_BeginPos.GetPosition().y);
			m_IsDead = false;
		}
	}
	else if(m_Attacking)
	{
		m_pAttackTrigger->SetActive(true);
		Attack();
		m_pAttackTrigger->Update();
	}
	else if (!m_Attacking)
	{
		m_pGameObject->GetComponent<svp::TriggerComponent>()->SetActive(true);
		m_pAttackTrigger->SetActive(false);
	}
}

void digdug::DigDugLogic::Render()
{
	if(m_AttackStage > 0)
		m_pAttackSprite->Render();
	m_pAttackTrigger->Render();
}

void digdug::DigDugLogic::OnTriggerEnter(svp::TriggerComponent * pOther)
{
	if (auto pFygar = pOther->GetGameObject()->GetComponent<FygarLogic>())
	{
		pFygar->SetScale(1.1f);
	}
}

void digdug::DigDugLogic::OnTriggerLeave(svp::TriggerComponent* pOther)
{
	if (auto pFygar = pOther->GetGameObject()->GetComponent<FygarLogic>())
	{
		pFygar->SetScale(1.f);
	}
}

void digdug::DigDugLogic::Respawn()
{
	m_IsDead = true;
}

void digdug::DigDugLogic::Attack()
{
	svp::Direction dir = m_pGameObject->GetComponent<svp::GraphMovementComponent>()->GetDirection();
	float x{}, y{};
	switch (dir)
	{
	case svp::Direction::DOWN:
		m_DirOfAttack = 270.f;
		y = m_pAttackSprite->GetTexture()->GetWidth() / 2.f;
		break;
	case svp::Direction::LEFT:
		m_DirOfAttack = 0.f;
		x = -m_pAttackSprite->GetTexture()->GetWidth() / 2.f;
		break;
	case svp::Direction::RIGHT:
		m_DirOfAttack = 180.f;
		x = m_pAttackSprite->GetTexture()->GetWidth() / 2.f;
		break;
	case svp::Direction::UP:
		m_DirOfAttack = 90.f;
		y = -m_pAttackSprite->GetTexture()->GetWidth() / 2.f;
		break;
	}

	m_pAttackSprite->SetOffset(x, y,m_DirOfAttack);

	if (m_AttackStage == 1)
	{
		m_pAttackSprite->SetTexture("Pump1");
	}
	else if (m_AttackStage == 2)
	{
		m_pAttackSprite->SetTexture("Pump2");
	}
	else if (m_AttackStage == 3)
	{
		m_pAttackSprite->SetTexture("Pump3");
	}
	else
		m_pAttackSprite->SetTexture("Pump0");

	SetTriggerOffset(dir, m_AttackStage);
}

void digdug::DigDugLogic::SetTriggerOffset(svp::Direction dir, int stage)
{
	float x{}, y{};
	switch (dir)
	{
	case svp::Direction::DOWN:
		if (stage == 1)
			y = 20.f;
		else if (stage == 2)
			y = 40.f;
		else if (stage == 3)
			y = 60.f;
		break;
	case svp::Direction::LEFT:
		if (stage == 1)
			x = -20.f;
		else if (stage == 2)
			x = -40.f;
		else if (stage == 3)
			x = -60.f;
		break;
	case svp::Direction::RIGHT:
		if (stage == 1)
			x = 20.f;
		else if (stage == 2)
			x = 40.f;
		else if (stage == 3)
			x = 60.f;
		break;
	case svp::Direction::UP:
		if (stage == 1)
			y = -20.f;
		else if (stage == 2)
			y = -40.f;
		else if (stage == 3)
			y = -60.f;
		break;
	}

	m_pAttackTrigger->SetOffset(x, y);
}
