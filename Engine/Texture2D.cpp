#include "pch.h"
#include "Texture2D.h"
#include <SDL.h>
#include "ResourceManager.h"

svp::Texture2D::Texture2D(SDL_Texture* pTexture)
	: m_pTexture{pTexture}
{
	UINT32 format;
	int access;
	SDL_QueryTexture(m_pTexture, &format, &access, &m_Width, &m_Height);
}

svp::Texture2D::Texture2D(std::string file)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(file)->GetSDLTexture();
}


svp::Texture2D::~Texture2D()
{
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
}
