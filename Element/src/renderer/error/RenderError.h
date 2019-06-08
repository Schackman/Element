#pragma once
#include <string_view>

namespace elm {namespace renderer { namespace err
{
	enum class Error : int
	{
		ok = 0, unknown = -1
	};
	template <Error E>
	inline constexpr int Code()
	{
		return static_cast<int>(Error);
	}
	template <Error E = Error::unknown>
	inline constexpr std::string_view Name() { return "unknown"; }

	template <>
	inline constexpr std::string_view Name<Error::ok>()
	{
		return "ok";
	}
}}}