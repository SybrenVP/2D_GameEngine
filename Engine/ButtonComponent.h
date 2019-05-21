#pragma once
#include "BaseComponent.h"
#include "../Game/ButtonCommands.h"

namespace svp
{
	enum class ButtonState
	{
		NORMAL,
		HIGHLIGHTED,
		SELECTED
	};

	class TextureComponent;
	class Transform;

	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(GameObject* const pGameObject, digdug::ButtonCommands* pCommand, TextureComponent* pButton = nullptr, TextureComponent* pHighlight = nullptr, TextureComponent* pSelect = nullptr, float xScale = 1, float yScale = 1);
		virtual ~ButtonComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override;

		ButtonState GetState() { return m_State; }
		void SetState(ButtonState state) { m_State = state; }

		void SetConnections(ButtonComponent* pLeft, ButtonComponent* pRight, ButtonComponent* pUp, ButtonComponent* pDown);

		void Right()
		{ 
			if (m_pButtonRight)
			{
				m_pButtonRight->SetState(ButtonState::HIGHLIGHTED);
				this->SetState(ButtonState::NORMAL);
			}
		}
		void Left()
		{
			if (m_pButtonLeft)
			{
				m_pButtonLeft->SetState(ButtonState::HIGHLIGHTED);
				this->SetState(ButtonState::NORMAL);
			}
		}
		void Up()
		{
			if (m_pButtonUp)
			{
				m_pButtonUp->SetState(ButtonState::HIGHLIGHTED);
				this->SetState(ButtonState::NORMAL);
			}
		}
		void Down()
		{
			if (m_pButtonDown)
			{
				m_pButtonDown->SetState(ButtonState::HIGHLIGHTED);
				this->SetState(ButtonState::NORMAL);
			}
		}

	private:
		TextureComponent* m_pButton;
		TextureComponent* m_pHighlighted;
		TextureComponent* m_pSelected;

		float m_XScale;
		float m_YScale;

		ButtonState m_State;

		ButtonComponent* m_pButtonLeft;
		ButtonComponent* m_pButtonRight;
		ButtonComponent* m_pButtonUp;
		ButtonComponent* m_pButtonDown;

		digdug::ButtonCommands* m_pCommand;
	};
}
