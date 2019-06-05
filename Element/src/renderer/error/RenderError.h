#pragma once

namespace elm {namespace renderer { namespace err
{
	enum class Error : int
	{
		ok = 0, unknown = -1
	};
	template <Error Error>
	inline int GetCode()
	{
		return static_cast<int>(Error);
	}
}}}
