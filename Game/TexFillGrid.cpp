#include "pch.h"
#include "TexFillGrid.h"

digdug::TexFillGrid::TexFillGrid(svp::GameObject * const pGameObject, svp::GridComponent * pGrid, svp::TextureComponent* pTex)
	: svp::BaseComponent(pGameObject)
	, m_pGrid(pGrid)
	, m_pBlock(pTex)
{
	m_pFreePointsOnGrid = m_pGrid->GetFreePoints();
	m_pPointsOnGrid = m_pGrid->GetPoints();
}

digdug::TexFillGrid::~TexFillGrid()
{
	delete m_pBlock;
}

void digdug::TexFillGrid::UpdateTextures()
{
	
}

void digdug::TexFillGrid::UpdateFreePoints()
{
	m_pPointsOnGrid = m_pGrid->GetPoints();
}

void digdug::TexFillGrid::Update()
{
	UpdateTextures();
	UpdateFreePoints();
}

void digdug::TexFillGrid::Render()
{
	for (auto point : m_pPointsOnGrid)
	{
		m_pBlock->SetOffset(point->GetPosition().x - m_pBlock->GetWidth() / 2.f, point->GetPosition().y - m_pBlock->GetHeight() / 2.f);
		m_pBlock->Render();
	}
}
