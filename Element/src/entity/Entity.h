#pragma once
#include "pch.h"

namespace elm
{
	namespace comp
	{
		class IComponent;
	}

	namespace entity
	{

		using EntityId = uint32_t;
		class Entity
		{
		public:
			explicit Entity() : 
				m_Id{ ++s_Id }
			{				
			}
			virtual ~Entity() = default;




		private:
			EntityId m_Id;
			static uint32_t s_Id;
		};
	}
}
