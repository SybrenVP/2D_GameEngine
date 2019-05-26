#include "pch.h"
#include "GridLoader.h"
#include <string>
#include "TransformComponent.h"
#include "GridComponent.h"

svp::GridLoader::GridLoader(GridComponent * pGrid, std::string file)
	: m_pGrid{ pGrid }
	, m_FileName{file}
{
}

svp::GridLoader::~GridLoader()
{
	m_In.close();
	for (auto point : m_pFreePoints)
	{
		delete point;
		point = nullptr;
	}
	m_pFreePoints.clear();
}

void svp::GridLoader::Open()
{
	m_In.open(m_FileName.c_str());
	if (!m_In)
	{
		Logger::GetInstance().Log(Logger::LogType::Error, "Failed to open gridloader file.");
		return;
	}
}

void svp::GridLoader::ReadPoints()
{
	int x{}, y{};

	while (m_In >> x && m_In >> y)
	{
		Transform* pTrans = new Transform(float(x), float(y));
		m_pFreePoints.push_back(pTrans);
	}

	m_pGrid->AddAsFreePoints(m_pFreePoints);
}
