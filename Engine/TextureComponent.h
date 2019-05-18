#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace svp
{
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(GameObject* const gameObject, const std::string& file, float posX = 0.f, float posY = 0.f);
		~TextureComponent();

		virtual void Update();
		virtual void Render();
		virtual void FixedUpdate() { return; }

	private:
		Texture2D* m_pTexture;
		float m_PosX;
		float m_PosY;
	};
}