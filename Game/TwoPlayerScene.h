#pragma once
#include "Scene.h"

namespace digdug
{
	class TwoPlayerScene : public svp::Scene
	{
	public:
		TwoPlayerScene();
		virtual ~TwoPlayerScene();

		TwoPlayerScene(const TwoPlayerScene& other) = delete;
		TwoPlayerScene(TwoPlayerScene&& other) noexcept = delete;
		TwoPlayerScene& operator=(const TwoPlayerScene& other) = delete;
		TwoPlayerScene& operator=(TwoPlayerScene&& other) noexcept = delete;

	private:
		void Initialize() override;
		void Update() override;
		void Render() const override;
	};
}
