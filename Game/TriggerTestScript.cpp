#include "pch.h"
#include "TriggerTestScript.h"


TriggerTestScript::TriggerTestScript(svp::GameObject* const pGameObject)
	: BaseComponent(pGameObject)
{
	m_Layer = LayerFlag::Trigger;
}

void TriggerTestScript::OnTriggerEnter(svp::TriggerComponent * pOther)
{
	svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "Own script ENTER");
	UNREFERENCED_PARAMETER(pOther);
}

void TriggerTestScript::OnTriggerLeave(svp::TriggerComponent * pOther)
{
	svp::Logger::GetInstance().Log(svp::Logger::LogType::Debug, "Own script LEAVE");
	UNREFERENCED_PARAMETER(pOther);
}

void TriggerTestScript::Update()
{
}

void TriggerTestScript::Render()
{
}

void TriggerTestScript::FixedUpdate()
{
}
