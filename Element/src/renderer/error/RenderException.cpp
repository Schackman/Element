#include "pch.h"
#include "RenderException.h"
#include <sstream>

namespace elm {namespace exception
{
	RenderException::RenderException(renderer::err::Error code, const std::string& reason) noexcept
		: Exception{reason},
		  m_ErrorCode(code),
		  m_Reason(reason)	
	{
	}

	const char* RenderException::what() const noexcept
	{
		std::stringstream s;
		s << "RenderException (" << Code(m_ErrorCode) << " reason: " << m_Reason;
		return s.str().c_str();
	}

	RenderException::~RenderException()
	{
	}
}}
