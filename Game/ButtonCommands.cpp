#include "pch.h"
#include "ButtonCommands.h"
#include "SceneManager.h"

void digdug::OnePlayer::Execute(svp::GameObject * pGameObject)
{
	//LoadScene here
	//svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "One player scene start");
	UNREFERENCED_PARAMETER(pGameObject);
	svp::SceneManager::GetInstance().SwitchScene("FPSScene");
}

void digdug::TwoPlayer::Execute(svp::GameObject* pGameObject)
{
	//LoadScene here
	svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "Two player scene start");
	UNREFERENCED_PARAMETER(pGameObject);
}