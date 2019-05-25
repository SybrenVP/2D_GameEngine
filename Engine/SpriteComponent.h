#pragma once
#include "BaseComponent.h"
#include <map>

namespace svp
{
	class TextureComponent;

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(GameObject* const pGameObject);
		virtual ~SpriteComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override;

		void SetTexture(std::string name);
		void AddTexture(std::string name, std::string file);
		void SetOffset(float x, float y, double angle);
		TextureComponent* GetTexture() { return m_pCurrentTexture; }
	private: 
		std::map<std::string, TextureComponent*> m_pTextures;
		TextureComponent* m_pCurrentTexture;
	};
}
