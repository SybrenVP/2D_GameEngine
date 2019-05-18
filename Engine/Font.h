#pragma once
#include "SDL_ttf.h"

namespace svp
{
	class Font
	{
	public:
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		TTF_Font* GetFont() const;

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

	private:
		TTF_Font* m_pFont;
		unsigned int m_Size;
	};
}