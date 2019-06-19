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
}}
