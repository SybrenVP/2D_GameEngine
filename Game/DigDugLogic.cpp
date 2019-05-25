#include "pch.h"
#include "DigDugLogic.h"
#include "GameTime.h"
#include "GraphMovementComponent.h"

digdug::DigDugLogic::DigDugLogic(svp::GameObject* const pGameObject, svp::SpriteComponent* pAttackSprite)
	: BaseComponent(pGameObject)
	, m_Attacking{false}
	, m_IsDead{false}
	, m_DirOfAttack{0.f}
	, m_AttackStage{0}
	, m_pAttackSprite{pAttackSprite}
{
	m_BeginPos = { 80.f, 40.f };
	m_pAttackSprite->SetTexture("Pump0");
}


digdug::DigDugLogic::~DigDugLogic()
{
	delete m_pAttackSprite;
}

void digdug::DigDugLogic::Update()
{
	if (m_IsDead)
	{
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
		Attack();
	}
}

void digdug::DigDugLogic::Render()
{
	if(m_AttackStage > 0)
		m_pAttackSprite->Render();
}

void digdug::DigDugLogic::OnTriggerEnter(svp::TriggerComponent * pOther)
{
	svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "Trigger Enter, do damage");
	UNREFERENCED_PARAMETER(pOther);
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
		m_pAttackSprite->SetTexture("Pump1");
	else if (m_AttackStage == 2)
		m_pAttackSprite->SetTexture("Pump2");
	else if (m_AttackStage == 3)
		m_pAttackSprite->SetTexture("Pump3");
	else
		m_pAttackSprite->SetTexture("Pump0");
}
