#pragma once
#include "GameObject.h"

namespace svp
{
	class InputCommands
	{
	public:
		virtual ~InputCommands() = default;
		virtual void Execute(GameObject* pGameObject, const int value = 0) = 0;
		virtual bool GetIsUp() { return m_IsUp; }

		virtual void Update() {}
		virtual void Render() {}
		virtual void FixedUpdate() {}

	protected:
		bool m_IsUp = true;
	};

	//Ingame movement
	class GridMoveDownCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class GridMoveLeftCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class GridMoveUpCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class GridMoveRightCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	//Ingame logic (attacking, idle...)
	class DigDugAttackCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	private:
		bool m_Attacking{};
	};

	class DigDugAttackStopCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	//Menuing
	class ButtonRightCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class ButtonLeftCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class ButtonUpCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class ButtonDownCommand final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};

	class ButtonSubmit final : public InputCommands
	{
		void Execute(GameObject* pGameObject, const int value = 0) override;
	};
}