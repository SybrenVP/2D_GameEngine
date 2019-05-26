#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace svp
{
	class GridComponent final : public BaseComponent, public Subject
	{
	public:
		GridComponent(GameObject* const pGameObject, const int width, const int height, const int space);
		// Width is the amount of points on the xAxis; height is the amount of points on the yAxis; space is the space inbetween the points.
		~GridComponent();

		virtual void Update() override;
		virtual void Render() override;
		virtual void FixedUpdate() override;

		int GetSpace() { return m_Space; }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		void AddAsFreePoints(std::vector<Transform*> pPoints);
		std::vector<Transform*> GetPoints() { return m_pPoints; }
		std::vector<Transform*> GetFreePoints() { return m_pFreePoints; }
		inline std::vector<int> GetXLines() { return m_XLines; }
		inline std::vector<int> GetYLines() { return m_YLines; }
		void GiveObjectPos(Transform pObjectTransform);
		void UpdateFreeLines();
		bool CheckIfPointIsFreePoint(Transform* point);

	private:
		std::vector<Transform*> m_pPoints;
		std::vector<Transform*> m_pFreePoints;
		std::vector<int> m_XLines;
		std::vector<int> m_YLines;
		Transform m_pObjectOnGridPosition;

		const int m_Width;
		const int m_Height;
		const int m_Space;
	};
}
