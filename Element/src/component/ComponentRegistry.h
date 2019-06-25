#pragma once
#include "Component.h"
namespace elm { namespace comp
{
	template <typename C>
	class ComponentRegistry final
	{
		ASSERT_COMPONENT_TYPE(C)
	public:

	private:
		std::vector<C> m_Components;
	};
}}
