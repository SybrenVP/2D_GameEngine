#include "pch.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Audio.h"

void svp::ResourceManager::Init(std::string && dataPath)
{
	m_DataPath = std::move(dataPath);

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "IMG_Init(PNG) error, in 'ResourceManager::Init()'.");
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	//if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	//{
	//	Logger::GetInstance().Log(Logger::LogType::Error, "IMG_Init(JPG) error, in 'ResourceManager::Init()'.");
	//	throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	//}

	if (TTF_Init() != 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "TTF_Init error, in 'ResourceManager::Init()'.");
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "MIx_OpenAudio error, in 'ResourceManager::Init()'.");
		throw std::runtime_error(std::string("Failed to load support for audio: ") + SDL_GetError());
	}
}

svp::Font* svp::ResourceManager::LoadFont(const std::string & file, unsigned int size)
{
	return new Font(m_DataPath + file, size);
}

svp::Texture2D* svp::ResourceManager::LoadTexture(const std::string & file)
{
	std::string fullPath = m_DataPath + file;
	
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if(!texture)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());

	return new Texture2D(texture);
}

Mix_Music* svp::ResourceManager::LoadMusic(const std::string & file)
{
	std::string fullPath = m_DataPath + file;

	Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
	if (!music)
		throw std::runtime_error(std::string("Failed to load audio: ") + SDL_GetError());
	
	return music;
}

Mix_Chunk* svp::ResourceManager::LoadSoundEffect(const std::string& file)
{
	std::string fullPath = m_DataPath + file;

	Mix_Chunk* sfx = Mix_LoadWAV(fullPath.c_str());
	if (!sfx)
		throw std::runtime_error(std::string("Failed to load SFX: ") + SDL_GetError());
	
	return sfx;
}
