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

	inline size_t Index(RenderTypes renderType)
	{
		return static_cast<size_t>(renderType);
	}

	inline constexpr size_t NrRenderTypes()
	{
		return static_cast<size_t>(RenderTypes::count);
	}

	template <RenderTypes R = RenderTypes::none>
	inline constexpr std::string_view RendererName()
	{
		return "none";
	};

}}

#define RENDERER_NAME(R) elm::renderer::RendererName<elm::renderer::RenderTypes::R>().data()
