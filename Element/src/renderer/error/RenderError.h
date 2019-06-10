#pragma once
#include <string_view>

namespace elm {namespace renderer { namespace err
{
	enum class Error : int
	{
		unknown = -1, ok = 0, null_ptr, glfw, opengl
	};

	inline constexpr int Code(Error e)
	{
		return static_cast<int>(e);
	}


	template <Error E = Error::unknown>
	inline constexpr std::string_view Name() { return "unknown"; }

	template <>
	inline constexpr std::string_view Name<Error::ok>()
	{
		return "ok";
	}
}}}
