#pragma once
#include "../entity/Entity.h"

namespace elm
{
	namespace comp
	{
		class IComponent
		{
		public:
			explicit IComponent() : m_Id{s_NextId++}
			{
			}
			virtual ~IComponent() = default;



		private:
			uint32_t m_Id;
			static uint32_t s_NextId;
		};

		uint32_t IComponent::s_NextId{ 1 };

	}
}
