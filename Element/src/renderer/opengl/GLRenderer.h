#pragma once
#include "../renderer.h"
struct WindowContext;
namespace elm { namespace renderer
{
	struct GLWindowInfo
	{
		GLFWwindow* windowHandle;		
	};

	class GLRenderer final : public Renderer
	{
	public:
		explicit GLRenderer() = default;
		virtual ~GLRenderer() override = default;
		virtual int Init(WindowContext* context) override;
		virtual void Render() const override;
		void Clear() const;
		virtual int ShutDown() override;
	private:
		void* m_pHandle;
		GLWindowInfo m_WindowInfo;
	};

}}
