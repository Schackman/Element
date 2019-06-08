#pragma once
#include <string>
namespace elm { namespace renderer
{
	class Renderer
	{
	public:
		Renderer() = default;

		virtual ~Renderer() = default;
		virtual int Init() = 0;
		virtual std::string GetName() const = 0;
	protected:
		virtual void Render() const = 0;
		virtual int ShutDown() = 0;
	};
}}
