#include "pch.h"
#include "GraphMovementComponent.h"
#include "GridComponent.h"
#include "Renderer.h"
#include <SDL.h>
#include "GameTime.h"
#include "CharacterControllerComponent.h"

svp::GraphMovementComponent::GraphMovementComponent(GameObject* const pGameObject, GridComponent* const pGrid, const int cornerCut)
	: BaseComponent(pGameObject)
	, m_pGrid{nullptr}
	, m_Space{pGrid->GetSpace()}
	, m_Width{pGrid->GetWidth()}
	, m_Height{pGrid->GetHeight()}
	, m_IsUsingGrid{true}
	, m_IsMoving{true}
	, m_Dir{Direction::NONE}
	, m_CornerCutoff{ cornerCut }
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

	if (m_pGameObject->GetComponent<CharacterControllerComponent>())
	{
		Transform trans = m_pGameObject->GetTransform();
		m_pGrid->GiveObjectPos(trans);
	}

	if (m_IsMoving)
	{
		if (m_Dir == Direction::UP && m_pGameObject->GetTransform().GetPosition().y > 40)
			MoveUp();
		else if (m_Dir == Direction::DOWN && m_pGameObject->GetTransform().GetPosition().y < 600)
			MoveDown();
		else if (m_Dir == Direction::LEFT && m_pGameObject->GetTransform().GetPosition().x > 40)
			MoveLeft();
		else if (m_Dir == Direction::RIGHT && m_pGameObject->GetTransform().GetPosition().x < 800)
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
	float yDisplacement{};
	float xDisplacement{};
	float speed{ 50.f };
	float deltaTime{float(GameTime::GetInstance().GetDeltaTime())};

	if (m_DistToClosestX <= m_CornerCutoff || !m_IsUsingGrid)
	{
		if (m_IsUsingGrid)
		{
			if (m_PreviousDir == Direction::LEFT)
				xDisplacement -= m_DistToClosestX;
			else if (m_PreviousDir == Direction::RIGHT)
				xDisplacement += m_DistToClosestX;
		}

		m_PreviousDir = Direction::UP;
		
		yDisplacement = -speed * deltaTime;
	}
	else if(m_PreviousDir == Direction::LEFT)
	{
		xDisplacement = -speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::RIGHT)
	{
		xDisplacement = speed * deltaTime;
	}

	m_pGameObject->Translate(xDisplacement, yDisplacement);
}

void svp::GraphMovementComponent::MoveDown()
{
	float yDisplacement{};
	float xDisplacement{};
	float speed{ 50.f };
	float deltaTime{ float(GameTime::GetInstance().GetDeltaTime()) };

	if (m_DistToClosestX <= m_CornerCutoff || !m_IsUsingGrid)
	{
		if (m_IsUsingGrid)
		{
			if (m_PreviousDir == Direction::LEFT)
				xDisplacement -= m_DistToClosestX;
			else if (m_PreviousDir == Direction::RIGHT)
				xDisplacement += m_DistToClosestX;
		}

		m_PreviousDir = Direction::DOWN;

		yDisplacement = speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::LEFT)
	{
		xDisplacement = -speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::RIGHT)
	{
		xDisplacement = speed * deltaTime;
	}

	m_pGameObject->Translate(xDisplacement, yDisplacement);
}

void svp::GraphMovementComponent::MoveLeft()
{
	float yDisplacement{};
	float xDisplacement{};
	float speed{ 50.f };
	float deltaTime{ float(GameTime::GetInstance().GetDeltaTime()) };

	if (m_DistToClosestY <= m_CornerCutoff || !m_IsUsingGrid)
	{
		if (m_IsUsingGrid)
		{
			if (m_PreviousDir == Direction::UP)
				yDisplacement -= m_DistToClosestY;
			else if (m_PreviousDir == Direction::DOWN)
				yDisplacement += m_DistToClosestY;
		}

		m_PreviousDir = Direction::LEFT;

		xDisplacement = -speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::UP)
	{
		yDisplacement = -speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::DOWN)
	{
		yDisplacement = speed * deltaTime;
	}

	m_pGameObject->Translate(xDisplacement, yDisplacement);
}

void svp::GraphMovementComponent::MoveRight()
{
	float yDisplacement{};
	float xDisplacement{};
	float speed{ 50.f };
	float deltaTime{ float(GameTime::GetInstance().GetDeltaTime()) };

	if (m_DistToClosestY <= m_CornerCutoff || !m_IsUsingGrid)
	{
		if (m_IsUsingGrid)
		{
			if (m_PreviousDir == Direction::UP)
				yDisplacement -= m_DistToClosestY;
			else if (m_PreviousDir == Direction::DOWN)
				yDisplacement += m_DistToClosestY;
		}

		m_PreviousDir = Direction::RIGHT;

		xDisplacement = speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::UP)
	{
		yDisplacement = -speed * deltaTime;
	}
	else if (m_PreviousDir == Direction::DOWN)
	{
		yDisplacement = speed * deltaTime;
	}

	m_pGameObject->Translate(xDisplacement, yDisplacement);
}

