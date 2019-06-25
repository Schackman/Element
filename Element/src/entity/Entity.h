#pragma once
#include "EntityId.h"
#include "component/Component.h"
#include "component/ComponentRegistry.h"
#include <bitset>

namespace elm
{
	class Entity
	{
	public:
		explicit Entity(EntityId id);

		template<typename C>
		bool HasComponent() const;

		template<typename C>
		C* GetComponent() const;

		template<typename C>
		void AddComponent();

		template<typename C>
		void RemoveComponent();


	private:
		const EntityId m_Id;
		std::bitset<16> m_ComponentFlags;
	};

	template <typename C>
	bool Entity::HasComponent() const
	{
		ASSERT_COMPONENT_TYPE(C);
		return m_ComponentFlags[C::id];
	}

	template <typename C>
	C* Entity::GetComponent() const
	{
		ASSERT_COMPONENT_TYPE(C);
		return comp::ComponentRegistry<C>::GetInstance().GetComponent(m_Id);
	}

	template <typename C>
	void Entity::AddComponent()
	{
		ASSERT_COMPONENT_TYPE(C);
		comp::ComponentRegistry<C>::GetInstance().AddComponent(m_Id);
		m_ComponentFlags[C::id] = true;
	}

	template <typename C>
	void Entity::RemoveComponent()
	{
		ASSERT_COMPONENT_TYPE(C);
		m_ComponentFlags[C::id] = false;
	}
}
