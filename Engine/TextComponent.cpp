//http://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/ 
//File based on instructions on this page ^
#include "pch.h"
#include "TextComponent.h"

#include "Renderer.h"

#include "Font.h"
#include "Texture2D.h"
//#include "GameObject.h"

svp::TextComponent::TextComponent(GameObject * const gameObject, const std::string & text, Font* font, const SDL_Color& color)
	: BaseComponent(gameObject)
	, m_Text{ text }
	, m_pFont{ font }
	, m_Color{ color }
{
}

svp::TextComponent::~TextComponent()
{
	if (m_pTexture)
		SDL_DestroyTexture(m_pTexture);
	if (m_pFont)
		delete m_pFont;
}

void svp::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);

		if(!surface)
			throw std::runtime_error(std::string("Creation of 'surface' failed: ") + SDL_GetError());
		else
		{
			m_pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
			if(!m_pTexture)
				throw std::runtime_error(std::string("Creation of 'texture' failed: ") + SDL_GetError());
		}

		SDL_FreeSurface(surface);
		surface = nullptr;
		m_NeedsUpdate = false;
	}
}

void svp::TextComponent::SetText(const std::string & text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void svp::TextComponent::Render()
{
	if (m_pTexture)
		Renderer::GetInstance().RenderTexture(m_pTexture, m_Transform.GetPosition().x, m_Transform.GetPosition().y, 0.f, 1.f);
	else
		m_NeedsUpdate = true;
}

void svp::TextComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

std::string svp::TextComponent::GetText()
{
	return m_Text;
}
