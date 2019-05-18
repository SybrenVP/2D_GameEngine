#include "pch.h"
#include "AudioLocator.h"

svp::Audio* svp::AudioLocator::m_AudioService{};
svp::NullAudio svp::AudioLocator::m_NullAudioService{};

void svp::AudioLocator::Initialize()
{ 
	m_AudioService = &m_NullAudioService; 
}

svp::Audio& svp::AudioLocator::GetAudio()
{
	return *m_AudioService;
}

void svp::AudioLocator::Provide(svp::Audio* audioService)
{
	if (audioService == NULL)
		m_AudioService = &m_NullAudioService;
	else
		m_AudioService = audioService;
}