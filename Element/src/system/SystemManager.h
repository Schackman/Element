#pragma once
#include "ISystem.h"

namespace elm
{
	namespace sys
	{
		enum class SystemType
		{
			renderer_vk
		};

		class SystemManager
		{
		public:
			SystemManager() = default;
			~SystemManager() = default;

			void CreateSystem(SystemType systemType);

		private:
			std::vector<std::unique_ptr<ISystem>> m_Systems;

			SystemManager(const SystemManager&) = delete;
			SystemManager(SystemManager&&) = delete;
			SystemManager operator=(const SystemManager&) = delete;
			SystemManager operator=(SystemManager&&) = delete;
		};
	}
}