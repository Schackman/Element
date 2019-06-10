#pragma once
#include "../RenderContext.h"
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace elm {
	namespace renderer
	{
		class GLContext final : public RenderContext
		{
		public:
			explicit GLContext(const core::Window::Handle& w, const core::APIVersion& api);
			void Init() override;
			void SwapBuffers() override;
			void Destroy() noexcept override;
			virtual ~GLContext() override;
		private:
			const GLFWwindow* m_pWindow;
			core::APIVersion m_Version;


			inline GLFWwindow* GetHandle() const { return const_cast<GLFWwindow*>(m_pWindow); }
		};

		template <>
		inline RenderContext* RenderContext::Create<core::GraphicsAPI::opengl>(core::Window::Handle window, const core::APIVersion& apiVersion)
		{
			return new GLContext{window, apiVersion};
		}
}}
