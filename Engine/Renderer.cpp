#include "pch.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "Texture2D.h"

void svp::Renderer::Initialize(SDL_Window * window)
{
	m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //always 60fps
	
	if (m_pRenderer == nullptr)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "SDL_CreateRenderer error, in 'Renderer::Initialize()'.");
		throw std::runtime_error(std::string("SDL_CreateRenderer error: ") + SDL_GetError());
	}
}

void svp::Renderer::Render() const
{
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_pRenderer);
}

void svp::Renderer::Destroy()
{
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void svp::Renderer::RenderTexture(SDL_Texture* texture, float x, float y, double angle) const
{
	SDL_Rect destRect{};
	destRect.x = static_cast<int>(x);
	destRect.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);

	//Render to screen
	SDL_RenderCopyEx(GetSDLRenderer(), texture, NULL, &destRect, angle, NULL, SDL_RendererFlip());
}

void svp::Renderer::RenderTexture(const Texture2D & texture, float x, float y, float width, float height) const
{
	SDL_Rect destRect{};
	destRect.x = static_cast<int>(x);
	destRect.y = static_cast<int>(y);
	destRect.w = static_cast<int>(width);
	destRect.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &destRect);
}
