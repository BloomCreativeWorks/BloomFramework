#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputDefinitions.h"

namespace bloom {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		InputManager() noexcept;

		void update();
		bool isKeyDown(KeyboardKey key) const noexcept;
		bool isKeyUp(KeyboardKey key) const noexcept;
		bool shift() const noexcept;
		bool ctrl() const noexcept;
		bool alt() const noexcept;
		bool isMouseDown(MouseButton button) const noexcept;
		bool isMouseUp(MouseButton button) const noexcept;
		bool isKeyPressed(KeyboardKey key) const noexcept;
		bool isMousePressed(MouseButton button) const noexcept;
		bool quitRequested() noexcept;
		int getMouseX() const noexcept;
		int getMouseY() const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		bool isMouseInside(const SDL_Rect& rectangle) const noexcept;
		std::string getPrintable() const noexcept;

	private:
		static bool isPrintable(SDL_Keycode key) noexcept;

		const uint8_t* m_keyboard = nullptr;

		uint32_t m_mouse = 0;

		int m_mouseX = 0, m_mouseY = 0;
		int m_mouseMoveX = 0, m_mouseMoveY = 0;
		int m_scrollX = 0, m_scrollY = 0;
		std::array<char, static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)> m_keyState;
		std::array<char, static_cast<size_t>(MouseButton::MOUSE_MAX)> m_mouseState;
		bool m_quitState = false;
		bool m_lockState = false;
		std::string m_printable{ "" };
	};
}