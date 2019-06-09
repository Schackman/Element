#pragma once
#include <type_traits>

#define BIT(N) (0b0001 << N)

#define ELM_REQUIRE_BASE(BASE, DERIVED) static_assert(std::is_base_of_v<BASE, DERIVED>)

#ifdef _DEBUG
#define ELM_DEBUG_ONLY(DebugCode) DebugCode
#else
#define ELM_DEBUG_ONLY(DebugCode)
#endif

