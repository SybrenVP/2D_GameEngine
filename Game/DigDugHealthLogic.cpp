#include "pch.h"
#include "DigDugHealthLogic.h"
#include "DigDugLogic.h"

digdug::DigDugHealthLogic::DigDugHealthLogic(svp::GameObject* const pGameObject, int health, svp::TextureComponent* pTex, svp::Transform* pPosOnScreen)
	: BaseComponent(pGameObject)
	, m_Health(health)
	, m_pHealthHeart(pTex)
	, m_pPos{pPosOnScreen}
{
}

digdug::DigDugHealthLogic::~DigDugHealthLogic()
{
	delete m_pHealthHeart;
	delete m_pPos;
}

void digdug::DigDugHealthLogic::Update()
{
}

void digdug::DigDugHealthLogic::Render()
{
	for (int i{}; i < m_Health; ++i)
	{
		m_pHealthHeart->SetOffset(m_pPos->GetPosition().x + m_pHealthHeart->GetWidth() * i, m_pPos->GetPosition().y);
		m_pHealthHeart->Render();
	}
}

void digdug::DigDugHealthLogic::Damage(int damage)
{
	m_Health -= damage;

	m_pGameObject->GetComponent<DigDugLogic>()->Respawn();
}
