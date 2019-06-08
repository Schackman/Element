#pragma once
namespace elm { namespace exception
{
	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const std::string& reason) noexcept;
	protected:
		virtual ~Exception() = default;
	};
}}
