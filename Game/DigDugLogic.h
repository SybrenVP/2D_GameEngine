#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "GraphMovementComponent.h"

namespace digdug
{
	class DigDugLogic : public svp::BaseComponent
	{
	public:
		DigDugLogic(svp::GameObject* const pGameObject, svp::SpriteComponent* pSprite, svp::TriggerComponent* pAttackTrigger);
		virtual ~DigDugLogic();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override {};

		virtual void OnTriggerEnter(svp::TriggerComponent* pOther) override;

		virtual void OnTriggerLeave(svp::TriggerComponent * pOther) override;

		void Respawn();
		bool IsAttacking() { return m_Attacking; }
		bool IsDead() { return m_IsDead; }
		void SetAttacking(bool val = true) { m_Attacking = val; }
		void SetAttackState(int state) { m_AttackStage = state; }
		svp::Transform GetPos() { return m_pGameObject->GetTransform(); }
	private:
		bool m_Attacking;
		bool m_IsDead;
		svp::Transform m_BeginPos;
		double m_DirOfAttack;
		int m_AttackStage;
		svp::SpriteComponent* m_pAttackSprite;
		svp::TriggerComponent* m_pAttackTrigger;

		void Attack();
		void SetTriggerOffset(svp::Direction dir, int stage);
	};
}
