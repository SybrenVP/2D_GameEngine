#pragma once
#include "Singleton.h"

namespace svp
{
	class GameTime final : public Singleton<GameTime>
	{
		class Timer
		{
		public:
			double time;
			bool finished;
			int index;
		};

	public:
		GameTime() = default;
		
		void Initialize();
		void Update();
		void UpdateLag();

		void SetMsPerUpdate(double msPerUpdate) { m_MsPerUpdate = msPerUpdate; }
		void SetTimer(double timer, int index);

		double GetDeltaTime() const { return (m_DeltaTime / 1000.f); }
		double GetLag() const { return m_Lag; }
		double GetMsPerUpdate() const { return m_MsPerUpdate; }
		double GetTotalTime() const { return m_TotalTime; }

		bool IsTimerFinished(int index);
		bool IsLagging() const { return m_Lag > m_MsPerUpdate; }

		void CleanupTimers();
		void RemoveTimer(int index);
	private:
		double m_DeltaTime{};
		double m_Lag{};
		double m_TotalTime{};
		double m_MsPerUpdate{0.20f};
		double m_PreviousTime{};
		std::vector<Timer> m_Timers{};

		void UpdateTimers();
	};
}