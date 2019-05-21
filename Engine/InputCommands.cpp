#include "pch.h"
#include "InputCommands.h"
#include "GraphMovementComponent.h"
#include "ButtonManagerComponent.h"

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

void svp::ButtonRightCommand::Execute(GameObject * pGameObject, const int )
{
	pGameObject->GetComponent<ButtonManagerComponent>()->NextRight();
}

void svp::ButtonLeftCommand::Execute(GameObject * pGameObject, const int )
{
	pGameObject->GetComponent<ButtonManagerComponent>()->NextLeft();
}

void svp::ButtonUpCommand::Execute(GameObject * pGameObject, const int )
{
	pGameObject->GetComponent<ButtonManagerComponent>()->NextUp();
}

void svp::ButtonDownCommand::Execute(GameObject * pGameObject, const int )
{
	pGameObject->GetComponent<ButtonManagerComponent>()->NextDown();
}

void svp::ButtonSubmit::Execute(GameObject* pGameObject, const int)
{
	pGameObject->GetComponent<ButtonManagerComponent>()->Submit();
}
