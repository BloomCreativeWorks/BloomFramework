#pragma once

#include "stdIncludes.h"
#include <bitset>
#include "InputDefinitions.h"
#include "Components/Position.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager;

	enum class EventType {
		NoEvent,
		QuitEvent,
		KeyboardEvent,
		MouseEvent,
		UnknownEvent
	};

	class BLOOMFRAMEWORK_API KeyboardEvent {
		friend class InputManager;

	public:
		KeyboardEvent() noexcept;

		// TODO: what's the point of this function?
		[[deprecated("Function 'isDown' is deprecated and will be removed soon. Use 'isPressed' instead.")]]
		bool isDown(KeyboardKey key) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated("Function 'isUp' is deprecated and will be removed soon. Use 'isPressed' instead.")]]
		bool isUp(KeyboardKey key) const noexcept;

		bool isPressed(KeyboardKey key) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		bool shift() const noexcept;
		bool ctrl() const noexcept;
		bool alt() const noexcept;
		bool capsLock() const noexcept;
		std::string getPrintable() const;

	private:
		void reset();
		void set(const SDL_KeyboardEvent& kbe) noexcept;
		static bool isPrintable(SDL_Keycode key) noexcept;
		void updateModKeys();

		std::bitset<static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)> m_keyboard{0};
		std::string m_printable{ "" };

		bool m_lockState = false;
	};

	class BLOOMFRAMEWORK_API MouseEvent {
		friend class InputManager;

	public:
		using Coordinates = components::Position;

		MouseEvent() noexcept;

		// TODO: what's the point of this function?
		[[deprecated("Function 'isDown' is deprecated and will be removed soon. Use 'isPressed' instead.")]]
		bool isDown(MouseButton button) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated("Function 'isUp' is deprecated and will be removed soon. Use 'isPressed' instead.")]]
		bool isUp(MouseButton button) const noexcept;

		uint8_t isPressed(MouseButton button) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		int getX() const noexcept;
		int getY() const noexcept;
		Coordinates getPos() const noexcept;
		Coordinates getOffset() const noexcept;
		Coordinates getScroll() const noexcept;
		bool isInside(const SDL_Rect& rectangle) const noexcept;

	private:
		void reset() noexcept;
		void set(const SDL_MouseButtonEvent& mbe) noexcept;
		void set(const SDL_MouseMotionEvent& mme) noexcept;
		void set(const SDL_MouseWheelEvent& mwe) noexcept;

		std::array<uint8_t, static_cast<size_t>(MouseButton::MOUSE_MAX)> m_mouse{};

		// TODO: ise Point instead of pair here
		Coordinates m_pos{ 0, 0 },
			m_offset{ 0, 0 },
			m_scroll{ 0, 0 };

		bool m_lockState = false;
	};
}
