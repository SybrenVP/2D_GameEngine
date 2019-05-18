#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "SDL.h"

namespace svp
{
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* gameObject, const std::string& text, Font* font, const SDL_Color& color = { 255,255,255 });
		virtual ~TextComponent();

		virtual void Update();
		void SetText(const std::string& text);
		virtual void Render();
		void SetPosition(float x, float y);
		std::string GetText();
		virtual void FixedUpdate() { return; }

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

	protected:
		std::string m_Text;
		Transform m_Transform;
		Font* m_pFont;
		SDL_Texture* m_pTexture;
		SDL_Color m_Color;
		bool m_NeedsUpdate;
	};
}