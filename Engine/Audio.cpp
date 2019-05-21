#include "pch.h"
#include "Audio.h"
#include "Logger.h"
#include "ResourceManager.h"

svp::ConsoleAudio::ConsoleAudio()
{
	m_pMusic.push_back(ResourceManager::GetInstance().LoadMusic("HappyDay.wav"));
	m_pSFX.push_back(ResourceManager::GetInstance().LoadSoundEffect("Woohoo.flac"));
}

svp::ConsoleAudio::~ConsoleAudio()
{
	for (auto music : m_pMusic)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}

	for (auto sfx : m_pSFX)
	{
		Mix_FreeChunk(sfx);
		sfx = nullptr;
	}
}

void svp::ConsoleAudio::PlayMusic(int i, int loops)
{
	Logger::GetInstance().Log(Logger::LogType::Debug, "Audio nr. " + std::to_string(i) + " starts playing.");
	Mix_PlayMusic(m_pMusic.at(i), loops);
}

void svp::ConsoleAudio::PauseMusic()
{
	if (Mix_PlayingMusic != 0)
		Mix_PauseMusic();
}

void svp::ConsoleAudio::ResumeMusic()
{
	if (Mix_PausedMusic != 0)
		Mix_ResumeMusic();
}

void svp::ConsoleAudio::StopMusic(int i)
{
	Logger::GetInstance().Log(Logger::LogType::Debug, "Audio nr. " + std::to_string(i) + " stops playing.");
	if (Mix_PlayingMusic != 0)
	{
		Mix_SetMusicPosition(0);
		Mix_PauseMusic();
	}
}

void svp::ConsoleAudio::PlaySoundEffect(int i, int channel)
{
	Mix_PlayChannel(channel, m_pSFX.at(i), 0);
}
