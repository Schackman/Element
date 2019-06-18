#pragma once
#include <string>
#include "../util/macro.h"

namespace elm { namespace event{
	enum class EventType
	{
		none = 0,
		key_pressed, key_released,
		mouse_button_down, mouse_button_up, mouse_move, mouse_scroll,
		window_close, window_resized, window_moved, window_focus_lost, window_focus,
		update, render
	};

	enum class EventCategory
	{
		// input categories get bits [0-4]
		input = 0b1111,
		keyboard = BIT(0) | BIT(1),
		mouse = BIT(2) | BIT(3),
		mouse_button = BIT(2),
		mouse_movement = BIT(3)
	};

	class Event
	{
	public:
		Event(EventType type, EventCategory category);
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual uint32_t GetCategories() const = 0;
		virtual std::string GetName() const	= 0;
		inline bool IsInCategory(EventCategory category);
	private:
		EventType m_Type;
		uint32_t m_CategoryFlags;
	};
}}
