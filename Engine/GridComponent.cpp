#include "pch.h"
#include "GridComponent.h"
#include "GridObserver.h"

svp::GridComponent::GridComponent(GameObject * const pGameObject, const int width, const int height, const int space)
	: BaseComponent(pGameObject)
	, m_Width{width}
	, m_Height{height}
	, m_Space{space}
{
	bool areYLinesDone{ false };

	//Generating all the points on the grid and creating lines in between them
	for (int i{}; i < width; i++)
	{
		for (int j{}; j < height; j++)
		{
			m_pPoints.push_back(new Transform(float(space + space * i), float(space + space * j)));

			if (!areYLinesDone)
				m_YLines.push_back(space + space * j);
		}
		areYLinesDone = true;

		m_XLines.push_back(space + space * i);
	}

	GridObserver* observer = new GridObserver();
	AddObserver(observer);

#ifdef DEBUG
	Logger::GetInstance().Log(Logger::LogType::Debug, "Created " + std::to_string(m_pPoints.size()) + " points on grid.");
	Logger::GetInstance().Log(Logger::LogType::Debug, "Saved " + std::to_string(m_XLines.size()) + " XLines.");
	Logger::GetInstance().Log(Logger::LogType::Debug, "Saved " + std::to_string(m_YLines.size()) + " YLines.");
#endif
}

svp::GridComponent::~GridComponent()
{
	const size_t size{ m_pPoints.size() };
	for (size_t i{}; i < size; i++)
	{
		delete m_pPoints.at(m_pPoints.size() - 1);
		m_pPoints.pop_back();
	}

	const size_t sizeFree{ m_pFreePoints.size() };
	for (size_t i{}; i < sizeFree; i++)
	{
		delete m_pFreePoints.at(m_pFreePoints.size() - 1);
		m_pFreePoints.pop_back();
	}
}

void svp::GridComponent::Update()
{
	UpdateFreeLines();
}

void svp::GridComponent::Render()
{
#ifdef DEBUG
	auto renderer{ Renderer::GetInstance().GetSDLRenderer() };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (const auto xLine : m_XLines)
	{
		SDL_RenderDrawLine(renderer, int(xLine) + 2, 0, int(xLine) + 2, 2000);
	}
	for (const auto yLine : m_YLines)
	{
		SDL_RenderDrawLine(renderer, 0, int(yLine) + 2, 2000, int(yLine) + 2);
	}
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 255);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (const auto point : m_pFreePoints)
	{
		SDL_RenderDrawLine(renderer, int(point->GetPosition().x) + 2, int(point->GetPosition().y) + 2, int(point->GetPosition().x) + m_Space + 2, int(point->GetPosition().y) + 2);
		SDL_RenderDrawLine(renderer, int(point->GetPosition().x) + 2, int(point->GetPosition().y) + 2, int(point->GetPosition().x) - m_Space + 2, int(point->GetPosition().y) + 2);
		SDL_RenderDrawLine(renderer, int(point->GetPosition().x) + 2, int(point->GetPosition().y) + 2, int(point->GetPosition().x) + 2, int(point->GetPosition().y) + m_Space + 2);
		SDL_RenderDrawLine(renderer, int(point->GetPosition().x) + 2, int(point->GetPosition().y) + 2, int(point->GetPosition().x) + 2, int(point->GetPosition().y) - m_Space + 2);
	}
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 255);
#endif
}

void svp::GridComponent::FixedUpdate()
{
}

void svp::GridComponent::GiveObjectPos(Transform pObjectTransform)
{
	m_pObjectOnGridPosition = pObjectTransform;
}

void svp::GridComponent::UpdateFreeLines()
{
	//Once we moved over a part of the grid it becomes 'free'
	for (size_t i{}; i < m_pPoints.size(); i++)
	{
		if (abs(m_pObjectOnGridPosition.GetPosition().x - m_pPoints[i]->GetPosition().x) <= m_Space / 2 &&
		abs(m_pObjectOnGridPosition.GetPosition().y - m_pPoints[i]->GetPosition().y) <= m_Space / 2)
		{
			m_pFreePoints.push_back(m_pPoints[i]);
			
			Notify(*m_pGameObject, Event::ADDING_FREEPOINT);
#ifdef DEBUG
			Logger::GetInstance().Log(Logger::LogType::Debug, "Adding point to freepoint list.");
#endif
			m_pPoints[i] = m_pPoints[m_pPoints.size() - 1];
			m_pPoints.pop_back();
		}
	}
}
