#pragma once
#include "Events.h"

namespace svp
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:
		virtual ~Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	private:
		static const unsigned int MAX_OBSERVERS{ 2 };
		Observer* m_pObservers[MAX_OBSERVERS];

	protected:
		void Notify(const GameObject& gameObj, Event e);
	};
}
