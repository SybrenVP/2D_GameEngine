#pragma once
#include "State.h"

namespace digdug
{
	class DigDugLogic;

	class DigDugState : public svp::State
	{
	public:
		virtual ~DigDugState() = default;

		virtual void Enter() = 0;
		virtual bool Update() = 0;
		virtual void Exit() = 0;

		void SetDigDug(DigDugLogic* pDig) { m_pDigDug = pDig; }
	protected:
		DigDugLogic* m_pDigDug;
	};

	class AttackState final : public DigDugState
	{
	public:
		virtual ~AttackState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};

	class IdleState final : public DigDugState
	{
	public:
		virtual ~IdleState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};

	class DeadState final : public DigDugState
	{
	public:
		virtual ~DeadState() = default;

		virtual void Enter() override;
		virtual bool Update() override;
		virtual void Exit() override;
	};
}
