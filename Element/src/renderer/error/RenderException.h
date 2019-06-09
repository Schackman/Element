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
	class RenderException : public Exception
	{
	public:
		explicit RenderException(renderer::err::Error code, const std::string& reason = "") noexcept;
		virtual char const* what() const noexcept override;
		virtual ~RenderException() override;
	private:
		const renderer::err::Error m_ErrorCode;
		const std::string m_Reason;
	};
}}
