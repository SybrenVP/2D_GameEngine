#pragma once
#include "Observer.h"

namespace svp
{
	class GameObject;

	class GridObserver : public Observer
	{
	public:
		virtual void OnNotify(const GameObject& gameObj, Event e);

	private:
		void UnlockAchievement(Achievement achievement);

		unsigned int m_AddedFreePoints{};
	};
}
