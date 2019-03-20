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
		class Entity
		{
		public:
			explicit Entity() : 
				m_Id{ s_NextId++ }
			{
				
			}
			virtual ~Entity() = default;


		private:
			uint32_t m_Id;
			std::vector<comp::IComponent> m_Components;

			static uint32_t s_NextId;
		};

	

		uint32_t Entity::s_NextId{ 1 };
	}
}
