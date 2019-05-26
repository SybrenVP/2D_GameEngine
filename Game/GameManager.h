#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

namespace digdug
{
	class GameManager final : public svp::BaseComponent
	{
	public:
		GameManager(svp::GameObject* const pGameObject);
		virtual ~GameManager();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override {};

		void AddEnemy(svp::GameObject* pEnemy);
		void AddPlayer(svp::GameObject* pPlayer);

	private:
		std::vector<svp::GameObject*> m_pEnemies;
		int m_AmtInactiveEnemy;
		std::vector<svp::GameObject*> m_pPlayers;
		int m_AmtInactivePlayer;
		svp::TextureComponent* m_pPlayerWins, *m_pEnemyWins;

		bool m_PlayerWins, m_EnemyWins;
	};
}
