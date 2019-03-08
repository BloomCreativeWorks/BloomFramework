#include "Input/InputEvents.h"

// checks keyboard key
#define checkKey(lockState, key) (!(lockState) && (key) != bloom::input::KeyboardKey::KEYBOARD_SIZE)
// checks mouse button
#define checkBtn(lockState, btn) (!(lockState) && (btn) != bloom::input::MouseButton::MOUSE_MAX)

// TODO: do we need this? (may be helpful for input fields)
//#define isLetter(key) ((key) >= SDLK_a && (key) <= SDLK_z)
//#define isDigit(key) ((key) >= SDLK_0 && (key) <= SDLK_9)
//#define isSpecialChar(key) ((key) == SDLK_MINUS || (key) == SDLK_EQUALS (key) == SDLK_COMMA || (key) == SDLK_SPACE \
//	|| (key) == SDLK_SEMICOLON || (key) == SDLK_QUOTE || (key) == SDLK_SLASH || (key) == SDLK_PERIOD \
//	|| (key) == SDLK_LEFTBRACKET || (key) == SDLK_RIGHTBRACKET || (key) == SDLK_BACKSLASH || (key) == SDLK_BACKQUOTE)

namespace bloom::input {
	KeyboardEvent::KeyboardEvent() noexcept {
		int numKeys = 0;
		auto kb = SDL_GetKeyboardState(&numKeys);
		size_t keys = std::min(static_cast<size_t>(numKeys), m_keyboard.size());
		for (size_t i = 0; i < keys; ++i) {
			m_keyboard[i] = kb[i];
		}
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

	bool KeyboardEvent::isPrintable(SDL_Keycode key) noexcept {
		return (key >= SDLK_SPACE && key <= SDLK_z || key == SDLK_RETURN || key == SDLK_BACKSPACE);
	}

	std::string KeyboardEvent::getPrintable() const {
		switch (m_printable) {
		case '\0':
			return std::string{ "" };

		case '\b':
			return std::string{ "\b \b" };

		case '\r':
			return std::string{ "\n" };

		default:
			return std::string{ m_printable };
		}
	}

	void KeyboardEvent::reset() {
		m_printable = '\0';
	}

	void KeyboardEvent::set(SDL_Keycode key, bool state) noexcept {
		//reset();
		if (state && isPrintable(key))
			m_printable = static_cast<char>(key);
		else
			m_printable = '\0';
	}



	MouseEvent::MouseEvent() noexcept {
		auto mouseState = SDL_GetMouseState(nullptr, nullptr);
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

	bool MouseEvent::isPressed(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button)
			&& m_mouse[static_cast<size_t>(button)]);
	}

	int MouseEvent::getX() const noexcept {
		return m_pos.first;
	}

	int MouseEvent::getY() const noexcept {
		return m_pos.second;
	}

	bool MouseEvent::isInside(const SDL_Rect & rectangle) const noexcept {
		return ((m_pos.first >= rectangle.x)
			&& (m_pos.first <= rectangle.x + rectangle.w)
			&& (m_pos.second >= rectangle.y)
			&& (m_pos.second <= rectangle.y + rectangle.h));
	}

	void MouseEvent::lock() noexcept {
		m_lockState = true;
	}

	void MouseEvent::unlock() noexcept {
		m_lockState = false;
	}

	void MouseEvent::reset() noexcept {
		m_scroll = { 0, 0 };
		m_offset = { 0, 0 };
	}

	void MouseEvent::set(std::pair<int32_t, int32_t> pos, std::pair<int32_t, int32_t> offset) noexcept {
		//reset();
		m_pos = std::move(pos);
		m_offset = std::move(offset);
	}

	void MouseEvent::set(uint8_t button, bool state) noexcept {
		//reset();
		m_mouse[button] = state;
	}

	void MouseEvent::set(std::pair<int32_t, int32_t> scroll) noexcept {
		//reset();
		m_scroll = std::move(scroll);
	}
}