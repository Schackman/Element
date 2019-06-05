#pragma once
#include "../renderer.h"

//#include <glm/glm.hpp>
struct WindowContext
{
	void* handle;
};
namespace elm { namespace renderer
{
	class GLRenderer final : public Renderer
	{
	public:
		explicit GLRenderer(WindowContext* context)
			: Renderer(context)
		{
			
		}

		virtual ~GLRenderer() override = default;
	protected:
		virtual int Init() override;
		virtual void Render() const override;
		virtual int ShutDown() override;
	};
}}
