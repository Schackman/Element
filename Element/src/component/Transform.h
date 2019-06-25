#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

namespace elm {namespace comp
{
	DEFINE_COMPONENT_TYPE(Transform)
	{
	public:
		explicit Transform();
		explicit Transform(float posX, float posY, float posZ);

		glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void Translate(float x, float y, float z);

		glm::vec3 GetRotation() const { return m_Rotation; }
		void SetRotation(float x, float y, float z);
		void Rotate(float x, float y, float z);

		glm::vec3 GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
		void Scale(float x, float y, float z);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}}
