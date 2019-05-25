#pragma once
#include "BaseComponent.h"

namespace digdug
{
	class PookaLogic final : public svp::BaseComponent
	{
	public:
		PookaLogic(svp::GameObject* const pGameObject);
		virtual ~PookaLogic();

		virtual void Update() override {};
		virtual void Render() override {};
		virtual void FixedUpdate() override {};
	private:

	};
}
