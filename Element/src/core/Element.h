#pragma once

namespace elm
{
	namespace core
	{
		class Window;

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
			Window* m_pWindow;
		};
	}
}