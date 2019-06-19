#pragma once
#include "glm/vec3.hpp"

namespace elm {namespace comp
{
	class Transform final
	{
	public:
		explicit Transform();
		explicit Transform(float posX, float posY, float posZ);
		glm::vec3 GetPosition() const { return m_Position; }
	private:
		glm::vec3 m_Position;
	};
}}
