#pragma once
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

		bool isPrintableKeyDown();
		std::string getCurPrintableKey();

	private:
		const uint8_t* m_keyboard;

		uint32_t m_mouse;

		int m_mouseX, m_mouseY;
		int m_mouseMoveX, m_mouseMoveY;
		int m_scrollX, m_scrollY;
		bool m_keyDown[KEYBOARD_SIZE];
		bool m_keyUp[KEYBOARD_SIZE];
		bool m_mouseDown[MOUSE_MAX];
		bool m_mouseUp[MOUSE_MAX];
		bool m_will_quit;
		int m_curPrintableKey;
		bool m_isLocked;
	};
}