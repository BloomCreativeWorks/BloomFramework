#include "Input/InputManager.h"

namespace bloom::input {
	bool InputManager::update(bool continueOnQuit) {
		reset();
		//keyboard.m_keyState.fill(0);
		//mouse.m_mouseState.fill(0);

		//mouse.m_mouseMoveX = 0;
		//mouse.m_mouseMoveY = 0;
		//keyboard.m_printable.reset();
		//keyboard.m_keyboard = SDL_GetKeyboardState(nullptr);
		//mouse.m_mouse = SDL_GetMouseState(&mouse.m_mouseX, &mouse.m_mouseY);

		bool caught = false;

		// Get key events from the OS
		while (SDL_PollEvent(&m_intlEvent)) {
			handle();
			caught = true;
			if (m_quitState && !continueOnQuit)
				break;
		}
		if (!caught)
			m_lastType = EventType::NoEvent;
		return caught;
	}

	EventType InputManager::wait(int timeout) {
		int caught;
		if (timeout < 0)
			caught = SDL_WaitEvent(&m_intlEvent);
		else
			caught = SDL_WaitEventTimeout(&m_intlEvent, timeout);
		if (caught)
			handle();
		else
			m_lastType = EventType::NoEvent;
		return m_lastType;
	}

	void InputManager::handle() {
		switch (m_intlEvent.type) {
		case SDL_QUIT: {
			m_lastType = EventType::QuitEvent;
			m_quitState = true;
			break;
		}
		case SDL_KEYDOWN: case SDL_KEYUP: {
			m_lastType = EventType::KeyboardEvent;
			keyboard.set(m_intlEvent.key);
			//SDL_Keysym pressedKey = m_intlEvent.key.keysym;

			//keyboard.m_keyState[pressedKey.scancode] = 1;

			//if (keyboard.isPrintable(pressedKey.sym)) {
			//	if (pressedKey.sym == SDLK_BACKSPACE)
			//		keyboard.m_printable = "\b \b";
			//	else
			//		keyboard.m_printable = pressedKey.sym;
			//}

			break;
		}
		case SDL_MOUSEMOTION: {
			m_lastType = EventType::MouseEvent;
			mouse.set(m_intlEvent.motion);
			//mouse.m_mouseX = m_intlEvent.motion.x;
			//mouse.m_mouseY = m_intlEvent.motion.y;
			//mouse.m_mouseMoveX = m_intlEvent.motion.xrel;
			//mouse.m_mouseMoveY = m_intlEvent.motion.yrel;
			break;
		}
		case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP: {
			m_lastType = EventType::MouseEvent;
			mouse.set(m_intlEvent.button);
			//mouse.m_mouseState[m_intlEvent.button.button] = 1;
			break;
		}
		case SDL_MOUSEWHEEL: {
			m_lastType = EventType::MouseEvent;
			mouse.set(m_intlEvent.wheel);
			//mouse.m_scrollX = m_intlEvent.wheel.x;
			//mouse.m_scrollY = m_intlEvent.wheel.y;
			break;
		}
		default:
			m_lastType = EventType::UnknownEvent;
			break;
		}
	}

	void InputManager::reset() {
		keyboard.reset();
		mouse.reset();
	}

	void InputManager::lock() noexcept {
		keyboard.lock();
		mouse.lock();
	}

	void InputManager::unlock() noexcept {
		keyboard.unlock();
		mouse.unlock();
	}

	bool InputManager::quitRequested() noexcept {
		auto tmp = m_quitState;
		m_quitState = false;
		return tmp;
	}

	//EventType InputManager::getType() const noexcept {
	//	return m_lastType;
	//}
}