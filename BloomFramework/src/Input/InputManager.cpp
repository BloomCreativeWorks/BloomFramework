#include "Input/InputManager.h"

// checks keyboard key
#define checkKey(lockState, key) (!lockState && key != bloom::KeyboardKey::KEYBOARD_SIZE)
// checks mouse button
#define checkBtn(lockState, btn) (!lockState && btn != bloom::MouseButton::MOUSE_MAX)

namespace bloom {
	InputManager::InputManager() noexcept :
		m_keyState(),
		m_mouseState()
	{}

	void InputManager::update() {
		for (int i = 0; i < static_cast<int>(KeyboardKey::KEYBOARD_SIZE); i++)
			m_keyState[i] = 0;

		for (int i = 0; i < static_cast<int>(MouseButton::MOUSE_MAX); i++)
			m_mouseState[i] = 0;

		m_mouseMoveX = 0;
		m_mouseMoveY = 0;
		m_printable.clear();
		m_keyboard = SDL_GetKeyboardState(nullptr);
		m_mouse = SDL_GetMouseState(&m_mouseX, &m_mouseY);

		// Get key events from the OS
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				m_quitState = true;
				break;
			}
			case SDL_KEYDOWN: {
				SDL_Keysym pressedKey = event.key.keysym;

				m_keyState[pressedKey.scancode] = 1;

				if (isPrintable(pressedKey.sym))

				break;
			}
			case SDL_KEYUP: {
				SDL_Keysym releasedKey = event.key.keysym;

				m_keyState[releasedKey.scancode] = -1;

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
				m_mouseState[event.button.button] = 1;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				m_mouseState[event.button.button] = -1;
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

	bool InputManager::isKeyDown(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == 1);
	}

	bool InputManager::isKeyUp(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == -1);
	}

	bool InputManager::isKeyPressed(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyboard
			&& static_cast<bool>(m_keyboard[static_cast<size_t>(key)]));
	}

	bool InputManager::shift() const noexcept {
		return (isKeyPressed(KeyboardKey::KEY_LEFT_SHIFT) || isKeyPressed(KeyboardKey::KEY_RIGHT_SHIFT));
	}

	bool InputManager::ctrl() const noexcept {
		return (isKeyPressed(KeyboardKey::KEY_LEFT_CTRL) || isKeyPressed(KeyboardKey::KEY_RIGHT_CTRL));
	}

	bool InputManager::alt() const noexcept {
		return (isKeyPressed(KeyboardKey::KEY_LEFT_ALT) || isKeyPressed(KeyboardKey::KEY_RIGHT_ALT));
	}

	bool InputManager::isMouseDown(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == 1);
	}

	bool InputManager::isMouseUp(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == -1);
	}

	bool InputManager::isMousePressed(MouseButton button) const noexcept {
		if (m_lockState)
			return false;

		switch (button)
		{
		case MouseButton::MOUSE_LEFT:
			return (m_mouse & SDL_BUTTON(1));

		case MouseButton::MOUSE_MIDDLE:
			return (m_mouse & SDL_BUTTON(2));

		case MouseButton::MOUSE_RIGHT:
			return (m_mouse & SDL_BUTTON(3));

		default:
			return false;
		}
	}

	int InputManager::getMouseX() const noexcept {
		return m_mouseX;
	}

	int InputManager::getMouseY() const noexcept {
		return m_mouseY;
	}

	bool InputManager::quitRequested() noexcept {
		bool curr = m_quitState;
		m_quitState = false;
		return curr;
	}

	bool InputManager::isMouseInside(const SDL_Rect& rectangle) const noexcept {
		return ((m_mouseX >= rectangle.x)
			&& (m_mouseX <= rectangle.x + rectangle.w)
			&& (m_mouseY >= rectangle.y)
			&& (m_mouseY <= rectangle.y + rectangle.h));
	}

	bool InputManager::isPrintable(SDL_Keycode key) noexcept {
		return (key >= SDLK_SPACE && key <= SDLK_z);
	}

	std::string InputManager::getPrintable() const noexcept {
		return m_printable;
	}

	void InputManager::lock() noexcept {
		m_lockState = true;
	}

	void InputManager::unlock() noexcept {
		m_lockState = false;
	}
}