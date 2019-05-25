#pragma once
#include "BaseComponent.h"
#include "Components.h"

namespace digdug
{
	class TexFillGrid final : public svp::BaseComponent
	{
	public:
		TexFillGrid(svp::GameObject* const pGameObject, svp::GridComponent* pGrid, svp::TextureComponent* pTex);
		virtual ~TexFillGrid();

		void UpdateTextures();
		void UpdateFreePoints();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override {};

	private:
		svp::GridComponent* m_pGrid;
		std::vector<svp::Transform*> m_pFreePointsOnGrid;
		std::vector<svp::Transform*> m_pPointsOnGrid;

		svp::TextureComponent* m_pBlock;
	};
}
