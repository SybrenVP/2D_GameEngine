#pragma once
#include "Audio.h"

namespace svp
{
	class Audio;

	class AudioLocator
	{
	public:
		static void DeleteAudioLocator();
		static void Initialize();
		static Audio& GetAudio();

		static void Provide(Audio* audioService);

	private:
		static Audio* m_pAudioService;
		static NullAudio m_NullAudioService;
	};
}