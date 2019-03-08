#include "Input/InputEvents.h"

// checks keyboard key
#define checkKey(lockState, key) (!(lockState) && (key) != bloom::input::KeyboardKey::KEYBOARD_SIZE)
// checks mouse button
#define checkBtn(lockState, btn) (!(lockState) && (btn) != bloom::input::MouseButton::MOUSE_MAX)

#define isLockKey(key) ((key) == SDL_SCANCODE_CAPSLOCK || (key) == SDL_SCANCODE_NUMLOCKCLEAR || (key) == SDL_SCANCODE_SCROLLLOCK)

namespace bloom::input {
	KeyboardEvent::KeyboardEvent() noexcept {
		int numKeys = 0;
		const auto kb = SDL_GetKeyboardState(&numKeys);
		const size_t keys = std::min(static_cast<size_t>(numKeys), m_keyboard.size());
		for (size_t i = 0; i < keys; ++i) {
			m_keyboard[i] = kb[i];
		}
		updateModKeys();
	}

	// TODO: what's the point of this function?
	bool KeyboardEvent::isDown(KeyboardKey key) const noexcept {
		//return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == 1);
		return isPressed(key);
	}

	// TODO: what's the point of this function?
	bool KeyboardEvent::isUp(KeyboardKey key) const noexcept {
		//return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == -1);
		return !isPressed(key);
	}

	bool KeyboardEvent::isPressed(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key)
			&& m_keyboard[static_cast<size_t>(key)]);
	}

	void KeyboardEvent::lock() noexcept {
		m_lockState = true;
	}

	void KeyboardEvent::unlock() noexcept {
		m_lockState = false;
	}

	bool KeyboardEvent::shift() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_SHIFT) || isPressed(KeyboardKey::KEY_RIGHT_SHIFT));
	}

	bool KeyboardEvent::ctrl() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_CTRL) || isPressed(KeyboardKey::KEY_RIGHT_CTRL));
	}

	bool KeyboardEvent::alt() const noexcept {
		return (isPressed(KeyboardKey::KEY_LEFT_ALT) || isPressed(KeyboardKey::KEY_RIGHT_ALT));
	}

	bool KeyboardEvent::capsLock() const noexcept {
		return isPressed(KeyboardKey::KEY_CAPSLOCK);
	}

	bool KeyboardEvent::isPrintable(SDL_Keycode key) noexcept {
		return (key >= SDLK_SPACE && key <= SDLK_z || key == SDLK_RETURN || key == SDLK_BACKSPACE);
	}

	void KeyboardEvent::updateModKeys() {
		const auto mod = SDL_GetModState();
		m_keyboard[SDL_SCANCODE_CAPSLOCK] = mod & KMOD_CAPS;
		m_keyboard[SDL_SCANCODE_NUMLOCKCLEAR] = mod & KMOD_NUM;
		// vvv	disable them	vvv
		//m_keyboard[SDL_SCANCODE_LSHIFT] = mod & KMOD_LSHIFT;
		//m_keyboard[SDL_SCANCODE_RSHIFT] = mod & KMOD_RSHIFT;
		//m_keyboard[SDL_SCANCODE_LCTRL] = mod & KMOD_LCTRL;
		//m_keyboard[SDL_SCANCODE_RCTRL] = mod & KMOD_RCTRL;
		//m_keyboard[SDL_SCANCODE_LALT] = mod & KMOD_LALT;
		//m_keyboard[SDL_SCANCODE_RALT] = mod & KMOD_RALT;
		//m_keyboard[SDL_SCANCODE_LGUI] = mod & KMOD_LGUI;
		//m_keyboard[SDL_SCANCODE_RGUI] = mod & KMOD_RGUI;
	}

	std::string KeyboardEvent::getPrintable() const {
		return m_printable;
	}

	void KeyboardEvent::reset() {
		m_printable.clear();
		updateModKeys();
	}

	void KeyboardEvent::set(const SDL_KeyboardEvent& kbe) noexcept {
		//reset();
		if (isLockKey(kbe.keysym.scancode)) {
			if (kbe.state)
				m_keyboard[kbe.keysym.scancode].flip();
		}
		else
			m_keyboard[kbe.keysym.scancode] = kbe.state;
		if (kbe.state && isPrintable(kbe.keysym.sym)) {
			if (kbe.keysym.sym == SDLK_BACKSPACE)
				m_printable += "\b ";
			m_printable += static_cast<char>(kbe.keysym.sym);
			if ((shift() || capsLock()) && kbe.keysym.sym >= SDLK_a && kbe.keysym.sym <= SDLK_z)
				m_printable.back() -= ('a' - 'A');
		}
	}



	MouseEvent::MouseEvent() noexcept {
		const auto mouseState = SDL_GetMouseState(nullptr, nullptr);
		for (size_t i = 1; i <= 3; ++i) {
			m_mouse[i] = mouseState & SDL_BUTTON(i);
		}
	}

	// TODO: what's the point of this function?
	bool MouseEvent::isDown(MouseButton button) const noexcept {
		//return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == 1);
		return isPressed(button);
	}

	// TODO: what's the point of this function?
	bool MouseEvent::isUp(MouseButton button) const noexcept {
		//return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == -1);
		return !isPressed(button);
	}

	uint8_t MouseEvent::isPressed(MouseButton button) const noexcept {
		if (checkBtn(m_lockState, button))
			return m_mouse[static_cast<size_t>(button)];
		return 0;
	}

	int MouseEvent::getX() const noexcept {
		return m_pos.x;
	}

	int MouseEvent::getY() const noexcept {
		return m_pos.y;
	}

	MouseEvent::Coordinates MouseEvent::getPos() const noexcept {
		return m_pos;
	}

	MouseEvent::Coordinates MouseEvent::getOffset() const noexcept {
		return m_offset;
	}

	MouseEvent::Coordinates MouseEvent::getScroll() const noexcept {
		return m_scroll;
	}

	bool MouseEvent::isInside(const SDL_Rect & rectangle) const noexcept {
		return ((m_pos.x >= rectangle.x)
			&& (m_pos.x <= rectangle.x + rectangle.w)
			&& (m_pos.y >= rectangle.y)
			&& (m_pos.y <= rectangle.y + rectangle.h));
	}

	void MouseEvent::lock() noexcept {
		m_lockState = true;
	}

	void MouseEvent::unlock() noexcept {
		m_lockState = false;
	}

	void MouseEvent::reset() noexcept {
		m_scroll.x = 0; m_scroll.y = 0;
		m_offset.x = 0; m_offset.y = 0;
	}

	void MouseEvent::set(const SDL_MouseButtonEvent & mbe) noexcept {
		//reset();
		//switch (mbe.state) {
		//case SDL_PRESSED:
		//	m_mouse[mbe.button] = mbe.clicks;
		//	break;
		//case SDL_RELEASED:
		//	m_mouse[mbe.button] = 0;
		//	break;
		//}
		m_mouse[mbe.button] = mbe.state ? mbe.clicks : 0;
		m_pos.x = mbe.x; m_pos.y = mbe.y;
	}

	void MouseEvent::set(const SDL_MouseMotionEvent & mme) noexcept {
		//reset();
		m_pos.x = mme.x; m_pos.y = mme.y;
		m_offset.x = mme.xrel; m_offset.y = mme.yrel;
	}

	void MouseEvent::set(const SDL_MouseWheelEvent & mwe) noexcept {
		//reset();
		m_scroll.x = mwe.x; m_scroll.y = mwe.y;
	}
}