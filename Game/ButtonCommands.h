#pragma once
#include "GameObject.h"

namespace digdug
{
	class ButtonCommands
	{
	public:
		virtual ~ButtonCommands() = default;
		virtual void Execute(svp::GameObject* pGameObject) = 0;
	};

	class OnePlayer final : public ButtonCommands
	{
		void Execute(svp::GameObject* pGameObject) override;
	};

	class TwoPlayer final : public ButtonCommands
	{
		void Execute(svp::GameObject* pGameObject) override;
	};
}
