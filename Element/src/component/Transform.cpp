#include "pch.h"
#include "Transform.h"

namespace elm {namespace comp
{
	Transform::Transform()
	{
	}

	Transform::Transform(float posX, float posY, float posZ)
		: m_Position(posX, posY, posZ)
	{
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		m_Position = {x, y, z};
	}

	void Transform::Translate(float x, float y, float z)
	{
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		m_Rotation = { x, y, z };
	}

	void Transform::Rotate(float x, float y, float z)
	{
		m_Rotation.x += x;
		m_Rotation.y += y;
		m_Rotation.z += z;
	}

	void Transform::SetScale(float x, float y, float z)
	{
		m_Scale = { x, y, z };
	}

	void Transform::Scale(float x, float y, float z)
	{
		m_Scale.x *= x;
		m_Scale.y *= y;
		m_Scale.z *= z;
	}
}}
