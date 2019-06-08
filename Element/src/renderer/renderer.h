#pragma once

namespace elm { namespace renderer
{
	class Renderer
	{
	public:
		Renderer() = default;

		virtual ~Renderer() = default;
		virtual int Init() = 0;
		virtual const std::string& GetName() const;
	protected:
		virtual void Render() const = 0;
		virtual int ShutDown() = 0;
	};
}}
