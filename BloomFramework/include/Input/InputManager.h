#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputDefinitions.h"

namespace bloom {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		InputManager();

		void update();
		bool isKeyDown(int key);
		bool isKeyUp(int key);
		bool shift();
		bool ctrl();
		bool alt();
		bool isMouseDown(MouseButton button);
		bool isMouseUp(MouseButton button);
		bool isKeyPressed(KeyboardKey key);
		bool isMousePressed(MouseButton button);
		bool quitRequested();
		int getMouseX();
		int getMouseY();
		void lock();
		void unlock();
		bool isMouseInside(SDL_Rect rectangle);
		static bool isPrintable(SDL_Keycode key);
		std::string getPrintable();

	private:
		const uint8_t* m_keyboard = nullptr;

		uint32_t m_mouse;

		int m_mouseX = 0, m_mouseY = 0;
		int m_mouseMoveX = 0, m_mouseMoveY = 0;
		int m_scrollX = 0, m_scrollY = 0;
		std::array<char, KEYBOARD_SIZE> m_keyState;
		std::array<char, KEYBOARD_SIZE> m_mouseState;
		bool m_will_quit = false;
		bool m_isLocked = false;
		std::string m_printable = "";
	};
}