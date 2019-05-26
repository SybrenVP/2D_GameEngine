#pragma once
#include "BaseComponent.h"
#include "GridComponent.h"

namespace digdug
{
	class DigDugLogic;

	class FygarLogic final : public svp::BaseComponent
	{
	public:
		FygarLogic(svp::GameObject* const pGameObject, svp::GridComponent* pGrid, DigDugLogic* pDigDug);
		virtual ~FygarLogic();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override {};

		virtual void OnTriggerEnter(svp::TriggerComponent* pOther) override;

		void MoveRandom();
		bool IsAttacking() { return m_IsAttacking; }
		bool IsGhost() { return m_IsGhost; }
		void SetScale(float scale) { m_Scale = scale; }
		float GetScale() { return m_Scale; }

		bool m_SetAttackScale = false;
	private: 
		bool m_IsAttacking;
		bool m_IsGhost;
		bool m_IsOnTarget;
		bool m_IsDead;
		svp::GridComponent* m_pGrid;
		svp::Transform* m_pPos;
		svp::Transform m_TargetPoint;
		DigDugLogic* m_pDigDug;
	
		float m_MovePercentage;
		float m_Scale;

		void SearchNewTargetWander();
		void SearchNewTargetGhost();
		void ChooseState();
		void MoveToTarget();
		float Sign(float val);
	};
}
