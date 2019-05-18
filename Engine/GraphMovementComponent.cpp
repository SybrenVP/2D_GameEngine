#include "pch.h"
#include "GraphMovementComponent.h"
#include "GridComponent.h"
#include "Renderer.h"
#include <SDL.h>
#include "GameTime.h"

svp::GraphMovementComponent::GraphMovementComponent(GameObject* const pGameObject, GridComponent* const pGrid)
	: BaseComponent(pGameObject)
	, m_pGrid{nullptr}
	, m_Space{pGrid->GetSpace()}
	, m_Width{pGrid->GetWidth()}
	, m_Height{pGrid->GetHeight()}
	, m_IsUsingGrid{true}
	, m_Dir{Direction::NONE}
{
	m_pGrid = pGrid;
	m_pPoints = m_pGrid->GetPoints();
	m_XLines = m_pGrid->GetXLines();
	m_YLines = m_pGrid->GetYLines();
}


svp::GraphMovementComponent::~GraphMovementComponent()
{
}

void svp::GraphMovementComponent::Update()
{
	// > What do we want this to do?:
	// We want to lock the movement of the gameObject on the grid (which is a separate component, on a separate gameobject)
	// Also we want a way to toggle this behavior off so we can have 2 ways of movement in the same game
	// > How do we want to do this?: 
	// When trying to move inbetween 2 grid points, we lock it to the nearest point/line //OLD way of doing it
	// NEW: Lerp in between the points
	
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;

	for (size_t i{}; i < m_XLines.size(); ++i)
	{
		if (gameObjX - m_XLines[i] <= m_Space / 2 && gameObjX - m_XLines[i] > -(m_Space / 2))
		{
			m_ClosestX = m_XLines[i];
			m_DistToClosestX = abs(int(gameObjX) - m_XLines[i]);
			break;
		}
	}

	for (size_t i{}; i < m_XLines.size(); ++i)
	{
		if (gameObjY - m_YLines[i] <= m_Space / 2 && gameObjY - m_YLines[i] > -(m_Space / 2))
		{
			m_ClosestY = m_YLines[i];
			m_DistToClosestY = abs(int(gameObjY) - m_YLines[i]);
			break;
		}
	}

	if (m_IsUsingGrid)
	{
		Transform trans = m_pGameObject->GetTransform();
		m_pGrid->GiveObjectPos(trans);

		if (m_Dir == Direction::UP)
			MoveUp();
		else if (m_Dir == Direction::DOWN)
			MoveDown();
		else if (m_Dir == Direction::LEFT)
			MoveLeft();
		else if (m_Dir == Direction::RIGHT)
			MoveRight();
	}

	//Resetting to NONE so we stop when we release the button
	if (m_Dir != Direction::NONE)
	{
		m_Dir = Direction::NONE;
	}
}

void svp::GraphMovementComponent::Render()
{
}

void svp::GraphMovementComponent::FixedUpdate()
{
}

void svp::GraphMovementComponent::SetDirection(Direction dir)
{
	m_Dir = dir;
}

void svp::GraphMovementComponent::MoveUp()
{	
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;

	if (m_DistToClosestX <= 2)
	{
		m_PreviousDir = Direction::UP;

		gameObjY--;
		gameObjX = float(m_ClosestX);
	}
	else if(m_PreviousDir == Direction::LEFT)
	{
		gameObjX--;
	}
	else if (m_PreviousDir == Direction::RIGHT)
	{
		gameObjX++;
	}

	m_pGameObject->SetPosition(gameObjX, gameObjY);
}

void svp::GraphMovementComponent::MoveDown()
{
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;

	if (m_DistToClosestX <= 2)
	{
		m_PreviousDir = Direction::DOWN;
		
		gameObjY++;
		gameObjX = float(m_ClosestX);
	}
	else if (m_PreviousDir == Direction::LEFT)
	{
		gameObjX--;
	}
	else if (m_PreviousDir == Direction::RIGHT)
	{
		gameObjX++;
	}

	m_pGameObject->SetPosition(gameObjX, gameObjY);
}

void svp::GraphMovementComponent::MoveLeft()
{
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;

	if (m_DistToClosestY <= 2)
	{
		m_PreviousDir = Direction::LEFT;

		gameObjX--;
		gameObjY = float(m_ClosestY);
	}
	else if (m_PreviousDir == Direction::UP)
	{
		gameObjY--;
	}
	else if (m_PreviousDir == Direction::DOWN)
	{
		gameObjY++;
	}

	m_pGameObject->SetPosition(gameObjX, gameObjY);
}

void svp::GraphMovementComponent::MoveRight()
{
	float gameObjX = m_pGameObject->GetTransform().GetPosition().x;
	float gameObjY = m_pGameObject->GetTransform().GetPosition().y;

	if (m_DistToClosestY <= 2)
	{
		m_PreviousDir = Direction::RIGHT;

		gameObjX++;
		gameObjY = float(m_ClosestY);
	}
	else if (m_PreviousDir == Direction::UP)
	{
		gameObjY--;
	}
	else if (m_PreviousDir == Direction::DOWN)
	{
		gameObjY++;
	}

	m_pGameObject->SetPosition(gameObjX, gameObjY);
}

