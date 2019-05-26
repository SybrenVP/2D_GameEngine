#pragma once
#include "BaseComponent.h"

namespace digdug
{
	class DigDugScoreLogic final : public svp::BaseComponent
	{
	public:
		DigDugScoreLogic(svp::GameObject* const pGameObject);
		virtual ~DigDugScoreLogic();

		virtual void Update() override {};
		virtual void Render() override {};
		virtual void FixedUpdate() override {};
	};
}
