#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "../lib/glm/glm/vec3.hpp"
#pragma warning(pop)

namespace svp
{
	class Transform final
	{
	public:
		Transform(float x = 0.f, float y = 0.f) :m_Position{ x, y, 0.0f } {}
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z)
		{
			m_Position = { x, y, z };
		}

		bool operator==(Transform& other) 
		{ 
			if (GetPosition().x == other.GetPosition().x &&
				GetPosition().y == other.GetPosition().y)
				return true;
			return false;
		}
	private:
		glm::vec3 m_Position;
	};
}