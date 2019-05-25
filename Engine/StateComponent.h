#pragma once
#include "BaseComponent.h"
#include <map>
namespace svp
{
	class State;

	class StateComponent : public BaseComponent
	{
	public:
		StateComponent(GameObject* const pGameObject, State* pCurrentState);
		virtual ~StateComponent();

		virtual void FixedUpdate() override {};
		virtual void Update() override;
		virtual void Render() override {};

	private:
		State* m_pCurrentState;
	};
}
