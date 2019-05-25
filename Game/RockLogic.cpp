#include "pch.h"
#include "RockLogic.h"
#include "GameTime.h"
#include "TriggerComponent.h"
#include "../Game/DigDugHealthLogic.h"

digdug::RockLogic::RockLogic(svp::GameObject* const pGameObject, svp::GridComponent* pGrid, svp::Transform posOnGrid)
	: BaseComponent(pGameObject)
	, m_pGrid(pGrid)
	, m_Pos(posOnGrid)
	, m_BottomIsFreePoint{false}
{
	m_pGridPoints = m_pGrid->GetPoints();
	m_pGameObject->SetPosition(m_Pos.GetPosition().x, m_Pos.GetPosition().y);

	for (size_t i{}, iSize{ m_pGridPoints.size() }; i < iSize; ++i)
	{
		if (m_Pos.GetPosition() == m_pGridPoints[i]->GetPosition())
		{
			m_PointUnderneath = *m_pGridPoints[i + 1]; //+1 means the point right underneath the one we just checked;
			break;
		}
	}

	m_Layer = LayerFlag::Trigger;
}


digdug::RockLogic::~RockLogic()
{
}

void digdug::RockLogic::Update()
{
	if (!m_BottomIsFreePoint)
		CheckBottomPoint();
	else if(svp::GameTime::GetInstance().IsTimerFinished(1))
		Fall();
}

void digdug::RockLogic::OnTriggerEnter(svp::TriggerComponent * pOther)
{
	svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "Trigger rock entered.");
	
	if (auto digdugHealth = pOther->GetGameObject()->GetComponent<DigDugHealthLogic>())
	{
		digdugHealth->Damage(1);
	}
}

void digdug::RockLogic::CheckBottomPoint()
{
	if (!m_pGrid->CheckIfPointIsFreePoint(&m_PointUnderneath))
		return;

	m_BottomIsFreePoint = true;

	double timerSec{ 3000 };
	svp::GameTime::GetInstance().SetTimer(timerSec, 1);
}

void digdug::RockLogic::Fall()
{
	int timesGoingDown{ 1 };
	for (size_t i{}; i < m_pGrid->GetPoints().size(); ++i)
	{
		svp::Transform tempTrans{ m_PointUnderneath.GetPosition().x, m_PointUnderneath.GetPosition().y + m_pGrid->GetSpace() * timesGoingDown };
		if (m_pGrid->CheckIfPointIsFreePoint(&tempTrans))
		{
			timesGoingDown++;
			continue;
		}
		else
		{
			m_PointToFallTo = tempTrans;
			break;
		}
	}

	if (m_PointToFallTo.GetPosition().y - m_pGameObject->GetTransform().GetPosition().y > 0.001)
	{
		float speed{ 100.f };
		float displacementY{ 0.f };

		displacementY = speed * float(svp::GameTime::GetInstance().GetDeltaTime());

		m_pGameObject->Translate(0.f, displacementY);
	}
	else if (m_PointToFallTo.GetPosition().y - m_pGameObject->GetTransform().GetPosition().y < 0.001)
	{
		m_pGameObject->SetActive(false);
	}
}