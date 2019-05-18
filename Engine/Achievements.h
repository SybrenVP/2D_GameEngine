#pragma once
#include <map>

namespace svp
{
	enum class Achievement
	{
		FIRST_STEPS,
		NR_OF_ACHIEVEMENTS
	};

	class Achievements : public Singleton<Achievements>
	{
	public:
		void Init()
		{
			for (int i{}; i < int(Achievement::NR_OF_ACHIEVEMENTS); ++i)
			{
				m_Achievements[Achievement(i)] = false;
			}
		}

		virtual void Unlock(Achievement achievement) 
		{ 
			m_Achievements[achievement] = true;
		}

		virtual bool GetIsUnlocked(Achievement achievement) 
		{ 
			return m_Achievements[achievement]; 
		}

	protected:
		std::map<Achievement, bool> m_Achievements;
	};
}