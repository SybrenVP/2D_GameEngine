#pragma once
#include "Scene.h"

namespace svp
{
	class FPSScene final : public Scene
	{
	public:
		FPSScene();
		virtual ~FPSScene();

		FPSScene(const FPSScene& other) = delete;
		FPSScene(FPSScene&& other) noexcept = delete;
		FPSScene& operator=(const FPSScene& other) = delete;
		FPSScene& operator=(FPSScene&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update() override;
		void Render() const override;
	};
}