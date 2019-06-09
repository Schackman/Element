#pragma once
#include "../renderer.h"
#include "../RenderTypes.h"

namespace elm { namespace renderer
{
	class GLRenderer final : public Renderer
	{
	public:
		explicit GLRenderer();
		virtual ~GLRenderer() override = default;
		virtual int Init() override;
		virtual void Render() const override;
		void Clear() const;
		virtual int ShutDown() override;
	};
}}
