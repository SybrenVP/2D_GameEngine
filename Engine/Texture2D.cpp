#include "pch.h"
#include "Texture2D.h"
#include <SDL.h>

svp::Texture2D::Texture2D(SDL_Texture* pTexture)
	: m_pTexture{pTexture}
{
}


svp::Texture2D::~Texture2D()
{
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
}
