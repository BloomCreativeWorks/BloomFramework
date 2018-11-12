#include "Input/InputManager.h"

namespace bloom {
	InputManager::InputManager() :
		m_keyboard(nullptr),
		m_mouse(0),
		m_mouseX(0),
		m_mouseY(0),
		m_will_quit(false),
		m_isLocked(false) {}

	void InputManager::update() {
		for (int i = 0; i < KEYBOARD_SIZE; i++) {
			m_keyDown[i] = false;
			m_keyUp[i] = false;
		}
		for (int i = 0; i < MOUSE_MAX; i++) {
			m_mouseDown[i] = false;
			m_mouseUp[i] = false;
		}
		m_mouseMoveX = 0;
		m_mouseMoveY = 0;
		m_curPrintableKey = 0;

		// Get key events from the OS
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				m_will_quit = true;
				break;
			}
			case SDL_KEYDOWN: {
				m_keyboard = SDL_GetKeyboardState(nullptr);
				SDL_Keysym pressedKey = event.key.keysym;

				m_keyDown[pressedKey.scancode] = true;

				if (InputManager::isPrintable(pressedKey.sym))
					m_curPrintableKey = pressedKey.sym;

				break;
			}
			case SDL_KEYUP: {
				m_keyboard = SDL_GetKeyboardState(nullptr);
				SDL_Keysym releasedKey = event.key.keysym;

				m_keyUp[releasedKey.scancode] = true;

				break;
			}
			case SDL_MOUSEMOTION: {
				m_mouseX = event.motion.x;
				m_mouseY = event.motion.y;
				m_mouseMoveX = event.motion.xrel;
				m_mouseMoveY = event.motion.yrel;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				m_mouse = SDL_GetMouseState(&(m_mouseX),
					&(m_mouseY));

				m_mouseDown[event.button.button] = true;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				m_mouse = SDL_GetMouseState(&(m_mouseX),
					&(m_mouseY));

				m_mouseDown[event.button.button] = true;
				break;
			}
			case SDL_MOUSEWHEEL: {
				m_scrollX = event.wheel.x;
				m_scrollY = event.wheel.y;
				break;
			}
			default:
				break;
			}
		}
	}

	bool InputManager::isKeyDown(int key) {
		if (m_isLocked) return false;

		if (key < 0 || key >= KEYBOARD_SIZE)
			return false;

		return (m_keyDown[key]);
	}

	bool InputManager::isKeyUp(int key) {
		if (m_isLocked) return false;

		if (key < 0 || key >= KEYBOARD_SIZE)
			return false;

		return (m_keyUp[key]);
	}

	bool InputManager::isKeyPressed(KeyboardKey key) {
		if (m_isLocked) return false;

		if (!(m_keyboard))
			return false;

		if (m_keyboard[key])
			return true;

		return false;
	}

	bool InputManager::shift() {
		return (isKeyPressed(KEY_LEFT_SHIFT) || isKeyPressed(KEY_RIGHT_SHIFT));
	}

	bool InputManager::ctrl() {
		return (isKeyPressed(KEY_LEFT_CTRL) || isKeyPressed(KEY_RIGHT_CTRL));
	}

	bool InputManager::alt() {
		return (isKeyPressed(KEY_LEFT_ALT) || isKeyPressed(KEY_RIGHT_ALT));
	}

	bool InputManager::isMouseDown(MouseButton button) {
		if (m_isLocked) return false;

		if (button == MOUSE_MAX)
			return false;

		return m_mouseDown[button];
	}

	bool InputManager::isMouseUp(MouseButton button) {
		if (m_isLocked) return false;

		if (button == MOUSE_MAX)
			return false;

		return m_mouseUp[button];
	}

	bool InputManager::isMousePressed(MouseButton button) {
		if (m_isLocked) return false;

		switch (button)
		{
		case MOUSE_LEFT:
			if (m_mouse & SDL_BUTTON(1))
				return true;
			break;

		case MOUSE_MIDDLE:
			if (m_mouse & SDL_BUTTON(2))
				return true;
			break;

		case MOUSE_RIGHT:
			if (m_mouse & SDL_BUTTON(3))
				return true;
			break;

		default:
			break;
		}

		return false;
	}

	int InputManager::getMouseX() {
		return m_mouseX;
	}

	int InputManager::getMouseY() {
		return m_mouseY;
	}

	bool InputManager::quitRequested() {
		bool curr = m_will_quit;
		m_will_quit = false;
		return curr;
	}

	bool InputManager::isMouseInside(SDL_Rect rectangle) {
		if ((m_mouseX >= rectangle.x) 
			&& (m_mouseX <= rectangle.x + rectangle.w)
			&& (m_mouseY >= rectangle.y) 
			&& (m_mouseY <= rectangle.y + rectangle.h))
			return true;

		return false;
	}

	bool InputManager::isPrintable(SDL_Keycode key) {
		return ((key > SDLK_SPACE) && (key < SDLK_z));
	}

	bool InputManager::isPrintableKeyDown() {
		return (InputManager::isPrintable(m_curPrintableKey));
	}

	std::string InputManager::getCurPrintableKey() {
		char c = static_cast<char>(m_curPrintableKey);;
		return (static_cast<std::string>(&c));
	}

	void InputManager::lock() {
		m_isLocked = true;
	}

	void InputManager::unlock() {
		m_isLocked = false;
	}
}