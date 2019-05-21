#pragma once
#include "BaseComponent.h"

namespace svp
{
	class StateComponent : public BaseComponent
	{
	public:
		StateComponent(GameObject* const pGameObject);
		virtual ~StateComponent();

		virtual void FixedUpdate() override {};
		virtual void Update() override {};
		virtual void Render() override {};

	private:

	};
}
