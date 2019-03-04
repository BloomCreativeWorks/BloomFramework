#include "Input/InputManager.h"

namespace bloom::input {
	void InputManager::update() {
		reset();

		//keyboard.m_keyState.fill(0);
		//mouse.m_mouseState.fill(0);

		//mouse.m_mouseMoveX = 0;
		//mouse.m_mouseMoveY = 0;
		//keyboard.m_printable.clear();
		//keyboard.m_keyboard = SDL_GetKeyboardState(nullptr);
		//mouse.m_mouse = SDL_GetMouseState(&mouse.m_mouseX, &mouse.m_mouseY);

		// Get key events from the OS
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				m_type = EventType::QuitEvent;
				break;
			}
			case SDL_KEYDOWN: {
				m_type = EventType::KeyboardEvent;
				keyboard.set(event.key.keysym, 1);
				//SDL_Keysym pressedKey = event.key.keysym;

				//keyboard.m_keyState[pressedKey.scancode] = 1;

				//if (keyboard.isPrintable(pressedKey.sym)) {
				//	if (pressedKey.sym == SDLK_BACKSPACE)
				//		keyboard.m_printable = "\b \b";
				//	else
				//		keyboard.m_printable = pressedKey.sym;
				//}

				break;
			}
			case SDL_KEYUP: {
				m_type = EventType::KeyboardEvent;
				keyboard.set(event.key.keysym, -1);
				//SDL_Keysym releasedKey = event.key.keysym;

				//keyboard.m_keyState[releasedKey.scancode] = -1;

				break;
			}
			case SDL_MOUSEMOTION: {
				m_type = EventType::MouseEvent;
				mouse.set(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				//mouse.m_mouseX = event.motion.x;
				//mouse.m_mouseY = event.motion.y;
				//mouse.m_mouseMoveX = event.motion.xrel;
				//mouse.m_mouseMoveY = event.motion.yrel;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				m_type = EventType::MouseEvent;
				mouse.set(event.button.button, 1);
				//mouse.m_mouseState[event.button.button] = 1;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				m_type = EventType::MouseEvent;
				mouse.set(event.button.button, -1);
				//mouse.m_mouseState[event.button.button] = -1;
				break;
			}
			case SDL_MOUSEWHEEL: {
				m_type = EventType::MouseEvent;
				mouse.set(event.wheel.x, event.wheel.y);
				//mouse.m_scrollX = event.wheel.x;
				//mouse.m_scrollY = event.wheel.y;
				break;
			}
			default:
				m_type = EventType::UnknownEvent;
				break;
			}
		}
	}

	void InputManager::reset() {
		keyboard.clear();
		mouse.clear();
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
		if (m_type == EventType::QuitEvent) {
			reset();
			return true;
		}
		return false;
	}

	EventType InputManager::getType() const noexcept {
		return m_type;
	}
}