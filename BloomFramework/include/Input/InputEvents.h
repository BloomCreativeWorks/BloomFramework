#pragma once

#include "stdIncludes.h"
#include "InputDefinitions.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager;

	enum class EventType {
		QuitEvent,
		KeyboardEvent,
		MouseEvent,
		UnknownEvent
	};

	class BLOOMFRAMEWORK_API KeyboardEvent {
		friend class InputManager;
		//using KeyboardKeys = std::array<char, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)>;

	public:
		KeyboardEvent() noexcept;

		// TODO: what's the point of this function?
		[[deprecated("Function 'isDown' is deprecated. Use 'isPressed' instead.")]]
		bool isDown(KeyboardKey key) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated("Function 'isUp' is deprecated. Use 'isPressed' instead.")]]
		bool isUp(KeyboardKey key) const noexcept;

		bool isPressed(KeyboardKey key) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		bool shift() const noexcept;
		bool ctrl() const noexcept;
		bool alt() const noexcept;
		std::string getPrintable() const;

	private:
		void reset();
		void set(SDL_Keycode key, bool state) noexcept;
		static bool isPrintable(SDL_Keycode key) noexcept;

		std::array<bool, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE) > m_keyboard{};
		char m_printable = '\0';

		bool m_lockState = false;
	};

	class BLOOMFRAMEWORK_API MouseEvent {
		friend class InputManager;

	public:
		MouseEvent() noexcept;

		// TODO: what's the point of this function?
		[[deprecated("Function 'isDown' is deprecated. Use 'isPressed' instead.")]]
		bool isDown(MouseButton button) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated("Function 'isUp' is deprecated. Use 'isPressed' instead.")]]
		bool isUp(MouseButton button) const noexcept;

		bool isPressed(MouseButton button) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		int getX() const noexcept;
		int getY() const noexcept;
		bool isInside(const SDL_Rect& rectangle) const noexcept;

	private:
		void reset() noexcept;
		void set(std::pair<int32_t, int32_t> pos, std::pair<int32_t, int32_t> movement) noexcept;
		void set(uint8_t button, bool state) noexcept;
		void set(std::pair<int32_t, int32_t> scroll) noexcept;

		std::array<bool, static_cast<size_t>(MouseButton::MOUSE_MAX)> m_mouse{};

		// TODO: ise Point instead of pair here
		std::pair<int32_t, int32_t> m_pos{ 0, 0 },
			m_offset{ 0, 0 },
			m_scroll{ 0, 0 };;

		bool m_lockState = false;
	};
}