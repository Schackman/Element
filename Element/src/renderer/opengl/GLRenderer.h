#pragma once
#include "../renderer.h"
#include "../RenderTypes.h"

namespace elm {
	struct WindowContext;
}

namespace elm { namespace renderer
{
	struct GLWindowInfo
	{
		GLFWwindow* handle;
		const std::string name;
	};

	class GLRenderer final : public Renderer
	{
	public:
		explicit GLRenderer(const WindowContext& context);
		virtual ~GLRenderer() override = default;
		virtual int Init() override;
		virtual void Render() const override;
		void Clear() const;
		virtual int ShutDown() override;
		virtual const std::string& GetName() const override;
	private:
		void* m_pHandle;
		GLWindowInfo m_WindowInfo;
	};
	template <RenderTypes T = RenderTypes::opengl>
	Renderer* CreateNewRenderer(const WindowContext& context)
	{
		return new GLRenderer{context};
	}
}}
