#include "pch.h"
#include "Font.h"

svp::Font::Font(const std::string & fullPath, unsigned int size)
	: m_pFont{ nullptr }
	, m_Size{ size }
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if(!m_pFont)
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

svp::Font::~Font()
{
	if (m_pFont)
	{
		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;
	}
}

TTF_Font * svp::Font::GetFont() const
{
	return m_pFont;
}
