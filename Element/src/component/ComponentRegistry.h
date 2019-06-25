#pragma once
#include "Component.h"
#include "entity/EntityId.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace elm
{
	class Entity;
}

namespace elm { namespace comp
{
	template <typename C>
	class ComponentRegistry final
	{
		friend elm::Entity;
		ASSERT_COMPONENT_TYPE(C)

		explicit ComponentRegistry(size_t reserved = 512U);


		C* GetComponent(EntityId entity) const;
		/**
		 * \return true if component was added.
		 */
		bool AddComponent(EntityId entity);
		std::vector<C> m_Components;
		std::unordered_map<EntityId, size_t> m_Registry;
	public :
		static ComponentRegistry<C>& GetInstance()
		{
			static ComponentRegistry<C> instance;
			return instance;
		}
	};

	template <typename C>
	ComponentRegistry<C>::ComponentRegistry(size_t reserved)
	{
		m_Components.reserve(reserved);
	}

	template <typename C>
	bool ComponentRegistry<C>::AddComponent(EntityId entity)
	{
		auto where = m_Registry.find(entity);
		if (where == m_Registry.end())
		{
			m_Components.push_back(C{});
			m_Registry.insert(where, std::make_pair(entity, m_Components.size() - 1));
			return true;
		}
		return false;
	}

	template <typename C>
	C* ComponentRegistry<C>::GetComponent(EntityId entity) const
	{
		auto where = m_Registry.find(entity);
		if (where == m_Registry.end())
		{
			return nullptr;
		}
		return const_cast<C*>(&m_Components[where->second]);
	}
}}
