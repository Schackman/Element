#pragma once

namespace elm { namespace renderer
{
	struct WindowContext;
	class Renderer
	{
	public:
		Renderer(WindowContext* context)
		{
		}

		virtual ~Renderer() = default;
	protected:
		virtual int Init() = 0;
		virtual void Render() const = 0;
		virtual int ShutDown() = 0;
	};
}}
