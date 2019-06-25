#include "pch.h"
#include "Entity.h"
#include "component/Transform.h"

namespace elm
{
	Entity::Entity(EntityId id)
		: m_Id(id), m_ComponentFlags{}
	{
		AddComponent<comp::Transform>();
	}
}
