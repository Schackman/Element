#include "pch.h"
#include "RenderException.h"
#include <sstream>

namespace elm {namespace exception
{
	RenderException::RenderException(renderer::err::Error code, const RendererInfo& info, const std::string& reason) noexcept
		: Exception{reason},
		  m_ErrorCode(code),
		  m_Info(info),
		  m_Reason(reason)	
	{
	}

	const char* RenderException::what() const noexcept
	{
		std::stringstream s;
		s << "RenderException in Renderer " << m_Info.name << ", reason: " << m_Reason;
		return s.str().c_str();
	}

	RenderException::~RenderException()
	{
	}
}}
