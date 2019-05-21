#include "AudioLocator.h"
#include "AudioLocator.h"
#include "pch.h"
#include "AudioLocator.h"

svp::Audio* svp::AudioLocator::m_pAudioService{};
svp::NullAudio svp::AudioLocator::m_NullAudioService{};

void svp::AudioLocator::DeleteAudioLocator()
{
	if (m_pAudioService)
		delete m_pAudioService;
}

void svp::AudioLocator::Initialize()
{ 
	m_pAudioService = &m_NullAudioService; 
}

svp::Audio& svp::AudioLocator::GetAudio()
{
	return *m_pAudioService;
}

void svp::AudioLocator::Provide(svp::Audio* audioService)
{
	if (audioService == NULL)
		m_pAudioService = &m_NullAudioService;
	else
		m_pAudioService = audioService;
}