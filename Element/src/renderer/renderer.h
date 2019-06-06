#pragma once

namespace elm { namespace renderer
{
	struct WindowContext
	{
		void* handle;
	};
	class Renderer
	{
	public:
		Renderer() = default;

		virtual ~Renderer() = default;
	protected:
		virtual int Init(WindowContext* context) = 0;
		virtual void Render() const = 0;
		virtual int ShutDown() = 0;
	};
}}
