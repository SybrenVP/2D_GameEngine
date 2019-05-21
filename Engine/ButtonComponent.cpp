#include "pch.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"

svp::ButtonComponent::ButtonComponent(GameObject * const pGameObject, digdug::ButtonCommands* pCommand,TextureComponent * pButton, TextureComponent * pHighlight, TextureComponent * pSelect, float xScale, float yScale)
	: BaseComponent(pGameObject)
	, m_pButton{pButton}
	, m_pHighlighted{pHighlight}
	, m_pSelected{pSelect}
	, m_XScale{xScale}
	, m_YScale{yScale}
	, m_pCommand{pCommand}
{
}

svp::ButtonComponent::~ButtonComponent()
{
	if (m_pButton)
		delete m_pButton;
	if (m_pHighlighted)
		delete m_pHighlighted;
	if (m_pSelected)
		delete m_pSelected;
	if (m_pCommand)
		delete m_pCommand;
}

void svp::ButtonComponent::Update()
{
	if (m_State == ButtonState::SELECTED)
	{
		m_pCommand->Execute(this->GetGameObject());
	}
}

void svp::ButtonComponent::Render()
{
	switch (m_State)
	{
	case ButtonState::NORMAL:
		m_pButton->Render();
		break;
	case ButtonState::HIGHLIGHTED:
		m_pHighlighted->Render();
		break;
	case ButtonState::SELECTED:
		m_pSelected->Render();
		break;
	}
}

void svp::ButtonComponent::FixedUpdate()
{
}

void svp::ButtonComponent::SetConnections(ButtonComponent * pLeft, ButtonComponent * pRight, ButtonComponent * pUp, ButtonComponent * pDown)
{
	m_pButtonLeft = pLeft;
	m_pButtonRight = pRight;
	m_pButtonUp = pUp;
	m_pButtonDown = pDown;
}
