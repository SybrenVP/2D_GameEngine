#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

namespace svp
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(GameObject* gameObject, Font* font, const SDL_Color& color);
		virtual ~FPSComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override { return; }
		void SetPosition(float x, float y);

	private:
		TextComponent* m_pText;
		int m_FPS;
		int m_FrameCounter;
	};
}