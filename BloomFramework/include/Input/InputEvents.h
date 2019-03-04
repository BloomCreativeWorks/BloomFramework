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
		using KeyboardKeys = std::array<char, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)>;

	public:
		// TODO: what's the point of this function?
		[[deprecated]]  bool isDown(KeyboardKey key) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated]] bool isUp(KeyboardKey key) const noexcept;

		bool isPressed(KeyboardKey key) const noexcept;
		void lock();
		void unlock();
		bool shift() const noexcept;
		bool ctrl() const noexcept;
		bool alt() const noexcept;
		std::string getPrintable() const noexcept;

	private:
		void clear();
		void set(SDL_Keysym key, int8_t keyState);
		static bool isPrintable(SDL_Keycode key) noexcept;

		const uint8_t* m_keyboard = nullptr;

		KeyboardKeys m_keyState{};
		std::string m_printable{ "" };

		bool m_lockState = false;
	};

	class BLOOMFRAMEWORK_API MouseEvent {
		friend class InputManager;
		using MouseButtons = std::array<char, static_cast<size_t>(MouseButton::MOUSE_MAX)>;

	public:
		// TODO: what's the point of this function?
		[[deprecated]] bool isDown(MouseButton button) const noexcept;
		// TODO: what's the point of this function?
		[[deprecated]] bool isUp(MouseButton button) const noexcept;

		bool isPressed(MouseButton button) const noexcept;
		void lock();
		void unlock();
		int getX() const noexcept;
		int getY() const noexcept;
		bool isInside(const SDL_Rect& rectangle) const noexcept;

	private:
		void clear();
		void set(int32_t x, int32_t y, int32_t moveX, int32_t moveY);
		void set(uint8_t button, int32_t state);
		void set(int32_t scrollX, int32_t scrollY);

		uint32_t m_mouse = 0;

		int32_t m_mouseX = 0, m_mouseY = 0,
			m_mouseMoveX = 0, m_mouseMoveY = 0,
			m_scrollX = 0, m_scrollY = 0;
		MouseButtons m_mouseState{};

		bool m_lockState = false;
	};
}