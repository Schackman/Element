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
			explicit GLContext();
			void Init() override;
			void Destroy() noexcept override;
			virtual ~GLContext() override;
		private:
			GLFWwindow* m_pWindow;
			static bool m_GLFWInitialized;

			static void ErrorCallback(int error, const char* message);
		};
}}
