#pragma once
#include "fwd.h"

namespace elm
{
	namespace core
	{
		class Core final
		{
		public:
			Core();
			Core(const Core&) = delete;
			Core(Core&&) = delete;
			~Core();

			Core& operator=(const Core&) = delete;
			Core& operator=(Core&&) = delete;

		private:
			IWindow* m_pWindow;
		};
	}
}