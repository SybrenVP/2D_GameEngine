#include "pch.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"


svp::TextureComponent::TextureComponent(GameObject* const gameObject, const std::string& file, float offsetX, float offsetY)
	: BaseComponent(gameObject)
	, m_pTexture{ nullptr }
	, m_OffsetX{ offsetX }
	, m_OffsetY{ offsetY }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(file);
	if (!m_pTexture)
		Logger::GetInstance().Log(Logger::LogType::Error, "Failed to load texture; In 'TextureComponent::TextureComponent'.");
	
	m_OffsetX = -(m_pTexture->GetWidth() * 0.5f) + offsetX;
	m_OffsetY = -(m_pTexture->GetHeight() * 0.5f) + offsetY;

	m_GameObjPosX = gameObject->GetTransform().GetPosition().x;
	m_GameObjPosY = gameObject->GetTransform().GetPosition().y;
}


svp::TextureComponent::~TextureComponent()
{
	if (m_pTexture)
		delete m_pTexture;
}

void svp::TextureComponent::Update()
{
	m_GameObjPosX = m_pGameObject->GetTransform().GetPosition().x;
	m_GameObjPosY = m_pGameObject->GetTransform().GetPosition().y;
}

void svp::TextureComponent::Render()
{
	if (m_pTexture)
		Renderer::GetInstance().RenderTexture(m_pTexture->GetSDLTexture(), m_GameObjPosX + m_OffsetX, m_GameObjPosY + m_OffsetY, m_Angle);
	else
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 0, 255); //Green means texture failed to load
		
		SDL_Rect rect{ int(m_pGameObject->GetTransform().GetPosition().x + 3), int(m_pGameObject->GetTransform().GetPosition().y + 3), 6, 6 };
		SDL_RenderFillRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}
}

int svp::TextureComponent::GetWidth()
{
	return m_pTexture->GetWidth();
}

int svp::TextureComponent::GetHeight()
{
	return m_pTexture->GetHeight();
}
