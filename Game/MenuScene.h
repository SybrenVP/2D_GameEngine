#pragma once
#include "Scene.h"

namespace digdug
{
	class MenuScene final : public svp::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		MenuScene(const MenuScene& other) = delete;
		MenuScene(MenuScene&& other) noexcept = delete;
		MenuScene& operator=(const MenuScene& other) = delete;
		MenuScene& operator=(MenuScene&& other) noexcept = delete;

	private:
		void Initialize() override;
		void Update() override;
		void Render() const override;
	};
}
