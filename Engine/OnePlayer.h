#pragma once
#include "Scene.h"

namespace digdug
{
	class OnePlayer final : public Scene
	{
	public:
		OnePlayer();
		virtual ~OnePlayer();

		OnePlayer(const OnePlayer& other) = delete;
		OnePlayer(OnePlayer&& other) noexcept = delete;
		OnePlayer& operator=(const OnePlayer& other) = delete;
		OnePlayer& operator=(OnePlayer&& other) noexcept = delete;

	private:
		void Initialize() override;
		void Update() override;
		void Render() const override;
	};
}