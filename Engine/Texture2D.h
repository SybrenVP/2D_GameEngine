#pragma once
struct SDL_Texture;

namespace svp
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const { return m_pTexture; }
		explicit Texture2D(SDL_Texture* pTexture);
		Texture2D(std::string file);
		~Texture2D();

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

	private:
		SDL_Texture* m_pTexture;
		int m_Width;
		int m_Height;
	};
}
