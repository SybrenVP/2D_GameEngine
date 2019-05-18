#include "pch.h"
#include "FPSComponent.h"
#include "GameTime.h"

svp::FPSComponent::FPSComponent(GameObject * gameObject, Font* font, const SDL_Color& color)
	: BaseComponent(gameObject)
	, m_pText{new TextComponent(gameObject, "", font, color)}
	, m_FPS{}
{
	std::string text = "FPS: ";
	m_pText->SetText(text);
}

svp::FPSComponent::~FPSComponent()
{
	if (m_pText)
		delete m_pText;
}

void svp::FPSComponent::Update()
{
	if (m_FrameCounter == 0) //If the framecounter is 0 this means the text has just flagged last frame to need an update the next frame
		m_pText->Update();

	//Taking the average FPS of 15 frames
	++m_FrameCounter;
	m_FPS += int(1 / GameTime::GetInstance().GetDeltaTime()); 
	if (m_FPS < 0)
		m_FPS = 0;
	if (m_FrameCounter == 15)
	{
		m_FPS /= 15;
		m_pText->SetText("FPS: " + std::to_string(m_FPS));
		m_FrameCounter = 0;
	}	
}

void svp::FPSComponent::Render()
{
	auto renderer = Renderer::GetInstance().GetSDLRenderer();

	SDL_Rect destRect{ int(m_pGameObject->GetTransform().GetPosition().x), int(m_pGameObject->GetTransform().GetPosition().y), 80, 35 };
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
	SDL_RenderFillRect(renderer, &destRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	m_pText->Render();
}

void svp::FPSComponent::SetPosition(float x, float y)
{
	m_pText->SetPosition(x, y);
}
