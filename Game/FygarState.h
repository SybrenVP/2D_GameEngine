#pragma once
#include "State.h"

namespace digdug
{
	class FygarLogic;

	class FygarState : public svp::State
	{
	public:
		virtual ~FygarState() = default;

		virtual void Enter() = 0;
		virtual bool Update() = 0;
		virtual void Exit() = 0;

		void SetFygar(FygarLogic* pFygar) { m_pFygar = pFygar; }

	protected:
		FygarLogic* m_pFygar;
	};

	class FygarAttackState final : public FygarState
	{
	public: 
		virtual ~FygarAttackState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};

	class WanderState final : public FygarState
	{
	public:
		virtual ~WanderState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};

	class GhostState final : public FygarState
	{
	public:
		virtual ~GhostState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};

	class BlowState final : public FygarState
	{
	public:
		virtual ~BlowState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};
}
