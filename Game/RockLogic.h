#pragma once
#include "BaseComponent.h"
#include "GridComponent.h"

namespace digdug
{
	class RockLogic final : public svp::BaseComponent
	{
	public:
		RockLogic(svp::GameObject* const pGameObject, svp::GridComponent* pGrid, svp::Transform posOnGrid);
		virtual ~RockLogic();

		virtual void Update() override;
		virtual void Render() override {};
		virtual void FixedUpdate() override {};

		virtual void OnTriggerEnter(svp::TriggerComponent* pOther);
	private:
		void CheckBottomPoint();
		void Fall();

		svp::GridComponent* m_pGrid;
		std::vector<svp::Transform*> m_pGridPoints;
		svp::Transform m_Pos;
		svp::Transform m_PointUnderneath;
		svp::Transform m_PointToFallTo;
		bool m_BottomIsFreePoint;
	};
}
