#include "pch.h"
#include "GameManager.h"
#include "DigDugHealthLogic.h"

digdug::GameManager::GameManager(svp::GameObject* const pGameObject)
	: BaseComponent(pGameObject)
	, m_EnemyWins{false}
	, m_PlayerWins{false}
	, m_pPlayerWins()
	, m_pEnemyWins()
{
	m_pPlayerWins = new svp::TextureComponent(m_pGameObject, "PlayerWins.png");
	m_pEnemyWins = new svp::TextureComponent(m_pGameObject, "PlayerLoses.png");
	m_pPlayerWins->SetOffset(0.f, 0.f);
	m_pEnemyWins->SetOffset(0.f, 0.f);
}

digdug::GameManager::~GameManager()
{
	delete m_pEnemyWins;
	delete m_pPlayerWins;
}

void digdug::GameManager::Update()
{
	for (size_t i{}, iSize{ m_pEnemies.size() }; i < iSize; ++i)
	{
		if (!m_pEnemies[i]->GetActive())
			++m_AmtInactiveEnemy;
	}

	for (size_t i{}, iSize{ m_pPlayers.size() }; i < iSize; ++i)
	{
		if (m_pPlayers[i]->GetComponent<digdug::DigDugHealthLogic>()->GetHealth() == 0)
			++m_AmtInactivePlayer;
	}

	if (m_AmtInactiveEnemy == int(m_pEnemies.size()))
	{
		m_EnemyWins = false;
		m_PlayerWins = true;
	}

	if (m_AmtInactivePlayer == int(m_pPlayers.size()))
	{
		m_EnemyWins = true;
		m_PlayerWins = false;
	}
}

void digdug::GameManager::Render()
{
	if (m_EnemyWins)
	{
		m_pEnemyWins->Render();
	}
	else if (m_PlayerWins)
	{
		m_pPlayerWins->Render();
	}
}

void digdug::GameManager::AddEnemy(svp::GameObject * pEnemy)
{
	m_pEnemies.push_back(pEnemy);
}

void digdug::GameManager::AddPlayer(svp::GameObject * pPlayer)
{
	m_pPlayers.push_back(pPlayer);
}
