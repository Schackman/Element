#include "pch.h"
#include "Exception.h"

elm::exception::Exception::Exception(const std::string& reason) noexcept
	: std::runtime_error(reason)
{
}
