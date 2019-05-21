#pragma once
#include "BaseComponent.h"

class svp::TriggerComponent;

class TriggerTestScript final : public svp::BaseComponent
{
public:
	TriggerTestScript(svp::GameObject* const pGameObject);
	virtual ~TriggerTestScript() = default;

	virtual void OnTriggerEnter(svp::TriggerComponent* pOther) override;
	virtual void OnTriggerLeave(svp::TriggerComponent* pOther) override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void FixedUpdate() override;

private:


};

