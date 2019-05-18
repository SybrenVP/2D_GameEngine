#include "pch.h"
#include "Subject.h"
#include "Observer.h"

svp::Subject::~Subject()
{
	for (int i{}; i < MAX_OBSERVERS; ++i)
	{
		delete m_pObservers[i];
	}
}

void svp::Subject::AddObserver(Observer * observer)
{
	for (int i{}; i < MAX_OBSERVERS; ++i)
	{
		if (m_pObservers[i] == nullptr)
		{
			m_pObservers[i] = observer;
			return;
		}
	}

	Logger::GetInstance().Log(Logger::LogType::Warning, "Couldn't add observer to list, In Subject::AddObserver().");
}

void svp::Subject::RemoveObserver(Observer * observer)
{
	for (int i{}; i < MAX_OBSERVERS; ++i)
	{
		if (m_pObservers[i] == observer)
		{
			if (i == MAX_OBSERVERS - 1)
			{
				delete m_pObservers[i];
				m_pObservers[i] = nullptr;
			}
			else if(i < MAX_OBSERVERS - 1)
			{
				m_pObservers[i] = m_pObservers[MAX_OBSERVERS - 1];
				delete m_pObservers[MAX_OBSERVERS - 1];
				m_pObservers[MAX_OBSERVERS - 1] = nullptr;
			}
			return;
		}
	}
}

void svp::Subject::Notify(const GameObject & gameObj, Event e)
{
	for (int i{}; i < MAX_OBSERVERS; ++i)
	{
		if(m_pObservers[i])
			m_pObservers[i]->OnNotify(gameObj, e);
	}
}
