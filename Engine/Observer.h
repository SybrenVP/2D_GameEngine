#pragma once
#include "Events.h"
#include "Achievements.h"

namespace svp
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const GameObject& gameObj, Event e) = 0;
	};
}
