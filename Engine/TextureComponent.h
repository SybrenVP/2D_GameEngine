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

		int GetWidth();
		int GetHeight();
		void SetOffset(float posX, float posY) 
		{
			m_OffsetX = posX;
			m_OffsetY = posY;
		}
		void AddToOffset(float posX, float posY)
		{
			m_OffsetX = -(m_pTexture->GetWidth() * 0.5f) + posX;
			m_OffsetY = -(m_pTexture->GetHeight() * 0.5f) + posY;
		}
		void SetAngle(double angle) { m_Angle = angle; }
		void SetUniformScale(float val) { m_Scale = val; }
	private:
		Texture2D* m_pTexture;
		float m_OffsetX;
		float m_OffsetY;

		float m_GameObjPosX;
		float m_GameObjPosY;

		float m_PosX;
		float m_PosY;
		double m_Angle;
		float m_Scale;
	};
}