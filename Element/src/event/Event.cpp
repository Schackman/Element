#include "pch.h"
#include "Event.h"

elm::event::Event::Event(EventType type, EventCategory category)
	: m_Type(type), m_CategoryFlags((uint32_t) category)
{
}

bool elm::event::Event::IsInCategory(EventCategory category)
{
	return m_CategoryFlags & (uint32_t)category;
}
