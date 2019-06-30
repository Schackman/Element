#pragma once
#include <type_traits>

namespace elm {namespace comp
{
	template <typename ComponentType>
	struct Component;
}}

#define ASSERT_COMPONENT_TYPE(T) static_assert(std::is_base_of_v<elm::comp::Component<T>, T>);

#define DEFINE_COMPONENT_TYPE(COMP)\
class COMP;\
template<> struct elm::comp::Component<COMP>\
{\
	inline constexpr static unsigned id = __COUNTER__ + 1;\
	inline constexpr static char name[] = #COMP;\
};\
class COMP final : public Component<COMP>
