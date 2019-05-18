#pragma once
#include "Singleton.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace svp
{
	class Texture2D;

	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_pRenderer = nullptr;

	public:
		void Initialize(SDL_Window* pWindow);
		void Render() const;
		void Destroy();

		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
	};
}
