#include "pch.h"
#include "InputCommands.h"
#include "GraphMovementComponent.h"

void svp::GridMoveDownCommand::Execute(GameObject* pGameObject, const int)
{
	pGameObject->GetComponent<GraphMovementComponent>()->SetDirection(svp::Direction::DOWN);
}

void svp::GridMoveLeftCommand::Execute(GameObject* pGameObject, const int)
{
	pGameObject->GetComponent<GraphMovementComponent>()->SetDirection(svp::Direction::LEFT);
}

void svp::GridMoveUpCommand::Execute(GameObject * pGameObject, const int)
{
	pGameObject->GetComponent<GraphMovementComponent>()->SetDirection(svp::Direction::UP);
}

void svp::GridMoveRightCommand::Execute(GameObject * pGameObject, const int)
{
	pGameObject->GetComponent<GraphMovementComponent>()->SetDirection(svp::Direction::RIGHT);
}
