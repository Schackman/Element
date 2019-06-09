#pragma once
#include "fwd.h"

namespace elm
{
	namespace core
	{
		class Element final
		{
		public:
			Element();
			Element(const Element&) = delete;
			Element(Element&&) = delete;
			~Element();

			Element& operator=(const Element&) = delete;
			Element& operator=(Element&&) = delete;

		private:
			IWindow* m_pWindow;
		};
	}
}