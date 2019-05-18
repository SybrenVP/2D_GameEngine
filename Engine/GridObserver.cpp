#include "pch.h"
#include "GridObserver.h"
#include "GameObject.h"
#include "Audio.h"
#include "AudioLocator.h"

void svp::GridObserver::OnNotify(const GameObject & , Event e)
{
	switch (e)
	{
	case Event::ADDING_FREEPOINT:
		++m_AddedFreePoints;
		if(m_AddedFreePoints == 5)
			UnlockAchievement(Achievement::FIRST_STEPS);
	}
}

void svp::GridObserver::UnlockAchievement(Achievement achievement)
{
	if (!Achievements::GetInstance().GetIsUnlocked(achievement))
	{
		Audio& soundEffect = AudioLocator::GetAudio();
		soundEffect.PlaySoundEffect(0, 0);
		Achievements::GetInstance().Unlock(achievement);
#ifdef DEBUG
		Logger::GetInstance().Log(Logger::LogType::Debug, "Achievement unlocked." );
#endif
	}
}
