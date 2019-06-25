#pragma once
#include <cstdint>
template <typename... ComponentTypes>
class ComponentRegistry;

namespace elm
{
	using EntityId = uint32_t;

	class Entity
	{
	public:
		explicit Entity(EntityId id)
			: m_Id(id)
		{
		}

		template<typename C>
		struct HasComponent
		{
			
		};

	private:
		const EntityId m_Id;
		

	};
}
