#pragma once
#include <typeinfo>

namespace elm { namespace comp
{
	template <typename... ComponentTypes>
	class ComponentRegistry final
	{
	private:
		constexpr static std::array<type_info, sizeof(ComponentTypes)> s_ComponentTypes{typeid(ComponentTypes)...};
	};
}}
