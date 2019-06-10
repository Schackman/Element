#pragma once
#include "../RenderContext.h"

struct GLFWwindow;

namespace elm { 
	namespace core
	{
		class IWindow;
	}

	namespace renderer
	{
		struct GLWindowInfo
		{
			union
			{
				void* nativeHandle;
				GLFWwindow* glfwHandle;
			};
			int apiVersionMajor;
			int apiVersionMinor;
		};

		class GLContext final : public RenderContext
		{
		public:
			explicit GLContext(GLFWwindow* w);
			void Init() override;
			void SwapBuffers() override;
			void Destroy() noexcept override;
			virtual ~GLContext() override;
		private:
			GLFWwindow* m_pWindow;

		};
}}
