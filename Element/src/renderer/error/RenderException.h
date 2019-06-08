#pragma once
#include "RenderError.h"
#include "../../exception/Exception.h"
#include <string>
#include "../RenderTypes.h"

namespace elm {namespace renderer
{
	class Renderer;
}}

namespace elm {namespace exception
{
	struct RendererInfo
	{
		renderer::Renderer* renderer;
		std::string name;
	};

	class RenderException : public Exception
	{
	public:
		explicit RenderException(renderer::err::Error code, const RendererInfo& info = {nullptr, RENDERER_NAME(none)},
		                         const std::string& reason = "") noexcept;
		virtual char const* what() const noexcept override;
		virtual ~RenderException() override;
	private:
		renderer::err::Error m_ErrorCode;
		RendererInfo m_Info;
		std::string m_Reason;
	};
}}
