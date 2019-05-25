#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

namespace digdug
{
	class DigDugHealthLogic final : public svp::BaseComponent
	{
	public:
		DigDugHealthLogic(svp::GameObject* const pGameObject, int health, svp::TextureComponent* pTex, svp::Transform* pPosOnScreen);
		virtual ~DigDugHealthLogic();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override {};

		void Damage(int damage);

	private:
		int m_Health;
		svp::TextureComponent* m_pHealthHeart;
		svp::Transform* m_pPos;
	};
}
