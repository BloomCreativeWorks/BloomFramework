#include "Input/InputManager.h"

// checks keyboard key
#define checkKey(lockState, key) (!lockState && key != bloom::KeyboardKey::KEYBOARD_SIZE)
// checks mouse button
#define checkBtn(lockState, btn) (!lockState && btn != bloom::MouseButton::MOUSE_MAX)

namespace bloom {
	InputManager::InputManager() noexcept :
		keyboard(),
		mouse()
	{}

	void InputManager::update() {
		for (int i = 0; i < static_cast<int>(KeyboardKey::KEYBOARD_SIZE); i++)
			keyboard.m_keyState[i] = 0;

		for (int i = 0; i < static_cast<int>(MouseButton::MOUSE_MAX); i++)
			mouse.m_mouseState[i] = 0;

		mouse.m_mouseMoveX = 0;
		mouse.m_mouseMoveY = 0;
		keyboard.m_printable.clear();
		keyboard.m_keyboard = SDL_GetKeyboardState(nullptr);
		mouse.m_mouse = SDL_GetMouseState(&mouse.m_mouseX, &mouse.m_mouseY);

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

				keyboard.m_keyState[pressedKey.scancode] = 1;

				if (keyboard.isPrintable(pressedKey.sym))

				break;
			}
			case SDL_KEYUP: {
				SDL_Keysym releasedKey = event.key.keysym;

				keyboard.m_keyState[releasedKey.scancode] = -1;

				break;
			}
			case SDL_MOUSEMOTION: {
				mouse.m_mouseX = event.motion.x;
				mouse.m_mouseY = event.motion.y;
				mouse.m_mouseMoveX = event.motion.xrel;
				mouse.m_mouseMoveY = event.motion.yrel;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				mouse.m_mouseState[event.button.button] = 1;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				mouse.m_mouseState[event.button.button] = -1;
				break;
			}
			case SDL_MOUSEWHEEL: {
				mouse.m_scrollX = event.wheel.x;
				mouse.m_scrollY = event.wheel.y;
				break;
			}
			default:
				break;
			}
		}
	}

	bool InputManager::Keyboard::isDown(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == 1);
	}

	bool InputManager::Keyboard::isUp(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == -1);
	}

	bool InputManager::Keyboard::isPressed(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyboard
			&& static_cast<bool>(m_keyboard[static_cast<size_t>(key)]));
	}

	bool InputManager::Keyboard::shift() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_SHIFT) || isPressed(KeyboardKey::KEY_RIGHT_SHIFT));
	}

	bool InputManager::Keyboard::ctrl() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_CTRL) || isPressed(KeyboardKey::KEY_RIGHT_CTRL));
	}

	bool InputManager::Keyboard::alt() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_ALT) || isPressed(KeyboardKey::KEY_RIGHT_ALT));
	}

	bool InputManager::Mouse::isDown(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == 1);
	}

	bool InputManager::Mouse::isUp(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == -1);
	}

	bool InputManager::Mouse::isPressed(MouseButton button) const noexcept {
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

	int InputManager::Mouse::getX() const noexcept {
		return m_mouseX;
	}

	int InputManager::Mouse::getY() const noexcept {
		return m_mouseY;
	}

	bool InputManager::quitRequested() noexcept {
		bool curr = m_quitState;
		m_quitState = false;
		return curr;
	}

	bool InputManager::Mouse::isInside(const SDL_Rect& rectangle) const noexcept {
		return ((m_mouseX >= rectangle.x)
			&& (m_mouseX <= rectangle.x + rectangle.w)
			&& (m_mouseY >= rectangle.y)
			&& (m_mouseY <= rectangle.y + rectangle.h));
	}

	bool InputManager::Keyboard::isPrintable(SDL_Keycode key) noexcept {
		return (key >= SDLK_SPACE && key <= SDLK_z);
	}

	std::string InputManager::Keyboard::getPrintable() const noexcept {
		return m_printable;
	}

	void InputManager::lock() noexcept {
		keyboard.m_lockState = true;
		mouse.m_lockState = true;
	}

	void InputManager::unlock() noexcept {
		keyboard.m_lockState = false;
		mouse.m_lockState = false;
	}
}