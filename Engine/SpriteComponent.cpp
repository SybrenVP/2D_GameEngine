#include "pch.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

svp::SpriteComponent::SpriteComponent(GameObject* const pGameObject)
	: BaseComponent(pGameObject)
{
}


svp::SpriteComponent::~SpriteComponent()
{
	for (auto tex : m_pTextures)
	{
		delete tex.second;
		tex.second = nullptr;
	}
	m_pTextures.clear();
}

void svp::SpriteComponent::Update()
{
	m_pCurrentTexture->Update();
}

void svp::SpriteComponent::Render()
{
	m_pCurrentTexture->Render();
}

void svp::SpriteComponent::FixedUpdate()
{
	m_pCurrentTexture->FixedUpdate();
}

void svp::SpriteComponent::SetTexture(std::string name)
{
	if (m_pTextures[name])
		m_pCurrentTexture = m_pTextures[name];
	else
		Logger::GetInstance().Log(Logger::LogType::Warning, "Texture with name: " + name + " not found, 'In SpriteComponent::SetTexture()'.");
	
	m_pCurrentTexture->Update();
}

void svp::SpriteComponent::AddTexture(std::string name, std::string file)
{
	if (!m_pTextures[name])
		m_pTextures[name] = new TextureComponent(m_pGameObject, file);
}

void svp::SpriteComponent::SetOffset(float x, float y, double angle)
{
	for (auto tex : m_pTextures)
	{
		tex.second->AddToOffset(x, y);
		tex.second->SetAngle(angle);
	}
}
