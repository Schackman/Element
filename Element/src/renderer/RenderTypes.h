#pragma once
#include <stdint.h>

namespace elm {namespace renderer
{
	using RendererId = uint16_t;

	const enum class RenderTypes : RendererId
	{
		none = 0,
		opengl = 1,
		vulkan = 2,
		count = 3
	};

	inline constexpr RenderTypes NrRenderTypes()
	{
		return RenderTypes::count;
	}
}}
