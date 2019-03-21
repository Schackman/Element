#pragma once
namespace elm { namespace exception
{
	class Exception : public std::exception
	{
	public:
		Exception() = default;
		virtual ~Exception() = default;
	};
}}
