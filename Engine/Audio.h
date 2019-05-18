#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>

namespace svp
{
	enum class Files
	{
		MUSIC = 0,
		EFFECT1 = 1
	};

	class Audio
	{
	public:
		virtual ~Audio() = default;
		
		virtual void PlayMusic(int soundID, int loops = -1) = 0;
		virtual void PauseMusic() = 0;
		virtual void ResumeMusic() = 0;
		virtual void StopMusic(int soundID) = 0;
		
		virtual void PlaySoundEffect(int soundID, int channel = 0) = 0;
	};

	class ConsoleAudio : public Audio
	{
	public:
		ConsoleAudio();
		virtual void PlayMusic(int soundID, int loops = -1);
		virtual void PauseMusic();
		virtual void ResumeMusic();
		virtual void StopMusic(int soundID);

		virtual void PlaySoundEffect(int soundID, int channel = 0);
	private:
		std::vector<Mix_Music*> m_pMusic;
		std::vector<Mix_Chunk*> m_pSFX;
	};

	class NullAudio : public Audio
	{
	public:
		NullAudio() {};
		virtual void PlayMusic(int, int) {};
		virtual void PauseMusic() {};
		virtual void ResumeMusic() {};
		virtual void StopMusic(int) {};

		virtual void PlaySoundEffect(int, int) {};
	};
}
