#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputDefinitions.h"

namespace bloom {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		InputManager() noexcept;

		class BLOOMFRAMEWORK_API Keyboard {
			friend class InputManager;

		public:
			bool isPressed(KeyboardKey key) const noexcept;
			bool isDown(KeyboardKey key) const noexcept;
			bool isUp(KeyboardKey key) const noexcept;
			bool shift() const noexcept;
			bool ctrl() const noexcept;
			bool alt() const noexcept;
			std::string getPrintable() const noexcept;

		private:
			const uint8_t* m_keyboard = nullptr;

			static bool isPrintable(SDL_Keycode key) noexcept;
			std::array<char, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)> m_keyState = std::array<char, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)>();
			std::string m_printable{ "" };

			bool m_lockState = false;
		} keyboard;
		
		class BLOOMFRAMEWORK_API Mouse {
			friend class InputManager;

		public:
			bool isDown(MouseButton button) const noexcept;
			bool isUp(MouseButton button) const noexcept;
			bool isPressed(MouseButton button) const noexcept;
			int getX() const noexcept;
			int getY() const noexcept;
			bool isInside(const SDL_Rect& rectangle) const noexcept;

		private:
			uint32_t m_mouse = 0;

			int m_mouseX = 0, m_mouseY = 0;
			int m_mouseMoveX = 0, m_mouseMoveY = 0;
			int m_scrollX = 0, m_scrollY = 0;

			std::array<char, static_cast<size_t>(MouseButton::MOUSE_MAX)> m_mouseState;

			bool m_lockState = false;
		} mouse;

		void update();
		bool quitRequested() noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		
	private:
		bool m_quitState = false;
		bool m_lockState = false;
	};
}