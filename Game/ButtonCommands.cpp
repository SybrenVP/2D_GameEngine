#include "pch.h"
#include "ButtonCommands.h"
#include "SceneManager.h"

void digdug::OnePlayerCommand::Execute(svp::GameObject * pGameObject)
{
	//LoadScene here
	//svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "One player scene start");
	UNREFERENCED_PARAMETER(pGameObject);
	svp::SceneManager::GetInstance().SwitchScene("OnePlayer");
}

void digdug::TwoPlayerCommand::Execute(svp::GameObject* pGameObject)
{
	//LoadScene here
	UNREFERENCED_PARAMETER(pGameObject);
	svp::SceneManager::GetInstance().SwitchScene("TwoPlayer");
}