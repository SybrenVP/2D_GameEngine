#pragma once
#include "BaseComponent.h"

namespace svp
{
	class GridComponent;
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

	class GraphMovementComponent final : public BaseComponent
	{
	public:
		GraphMovementComponent(GameObject* const pGameObject, GridComponent* const grid, const int cornerCut = 0);
		~GraphMovementComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override;

		void SetIsUsingGrid(bool usingGrid) { m_IsUsingGrid = usingGrid; }
		bool GetIsUsingGrid() { return m_IsUsingGrid; }
		void SetMovement(bool val) { m_IsMoving = val; }
		void SetDirection(Direction dir);
		Direction GetDirection() 
		{ 
			if (m_Dir != Direction::NONE)
				return m_Dir;
			else
				return m_PreviousDir;
		}

	private:
		std::vector<Transform*> m_pPoints;
		std::vector<int> m_XLines;
		std::vector<int> m_YLines;
		GridComponent* m_pGrid;
		
		Direction m_Dir;
		Direction m_PreviousDir;

		std::pair<float, float> m_Target;
		
		const int m_Width;
		const int m_Height;
		const int m_Space;
		const int m_CornerCutoff;

		int m_DistToClosestX;
		int m_DistToClosestY;
		int m_ClosestX;
		int m_ClosestY;

		bool m_IsUsingGrid;
		bool m_IsMoving;

		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
	};
}