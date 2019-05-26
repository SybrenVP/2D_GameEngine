#pragma once
#include <fstream>

namespace svp
{
	class GridComponent;
	class Transform;

	class GridLoader
	{
	public:
		GridLoader(svp::GridComponent* pGrid, std::string file);
		virtual ~GridLoader();

		void Open();
		void ReadPoints();
	private:
		svp::GridComponent* m_pGrid;
		std::string m_FileName;
		std::vector<Transform*> m_pFreePoints;
		std::ifstream m_In;

	};
}
