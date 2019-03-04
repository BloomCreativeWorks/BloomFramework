#include "Input/InputEvents.h"

// checks keyboard key
#define checkKey(lockState, key) (!(lockState) && (key) != bloom::input::KeyboardKey::KEYBOARD_SIZE)
// checks mouse button
#define checkBtn(lockState, btn) (!(lockState) && (btn) != bloom::input::MouseButton::MOUSE_MAX)

// TODO: do we need this?
//#define isLetter(key) ((key) >= SDLK_a && (key) <= SDLK_z)
//#define isDigit(key) ((key) >= SDLK_0 && (key) <= SDLK_9)
//#define isSpecialChar(key) ((key) == SDLK_MINUS || (key) == SDLK_EQUALS (key) == SDLK_COMMA || (key) == SDLK_SPACE \
//	|| (key) == SDLK_SEMICOLON || (key) == SDLK_QUOTE || (key) == SDLK_SLASH || (key) == SDLK_PERIOD \
//	|| (key) == SDLK_LEFTBRACKET || (key) == SDLK_RIGHTBRACKET || (key) == SDLK_BACKSLASH || (key) == SDLK_BACKQUOTE)

namespace bloom::input {

	// TODO: what's the point of this function?
	bool KeyboardEvent::isDown(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == 1);
	}

	// TODO: what's the point of this function?
	bool KeyboardEvent::isUp(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyState[static_cast<size_t>(key)] == -1);
	}

	bool KeyboardEvent::isPressed(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key) && m_keyboard
			&& static_cast<bool>(m_keyboard[static_cast<size_t>(key)]));
	}

	void KeyboardEvent::lock() {
		m_lockState = true;
	}

	void KeyboardEvent::unlock() {
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
		return (key == SDLK_BACKSPACE || (key >= SDLK_SPACE && key <= SDLK_z));
	}

	std::string KeyboardEvent::getPrintable() const noexcept {
		return m_printable;
	}

	void KeyboardEvent::clear() {
		m_keyState.fill(0);
		m_printable.clear();
		m_keyboard = SDL_GetKeyboardState(nullptr);
	}

	void KeyboardEvent::set(SDL_Keysym key, int8_t keyState) {
		//clear();
		m_keyState[key.scancode] = keyState;

		if (keyState == 1 && isPrintable(key.sym))
			m_printable = static_cast<char>(key.sym);
	}



	// TODO: what's the point of this function?
	bool MouseEvent::isDown(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == 1);
	}

	// TODO: what's the point of this function?
	bool MouseEvent::isUp(MouseButton button) const noexcept {
		return (checkBtn(m_lockState, button) && m_mouseState[static_cast<size_t>(button)] == -1);
	}

	bool MouseEvent::isPressed(MouseButton button) const noexcept {
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

	int MouseEvent::getX() const noexcept {
		return m_mouseX;
	}

	int MouseEvent::getY() const noexcept {
		return m_mouseY;
	}

	bool MouseEvent::isInside(const SDL_Rect & rectangle) const noexcept {
		return ((m_mouseX >= rectangle.x)
			&& (m_mouseX <= rectangle.x + rectangle.w)
			&& (m_mouseY >= rectangle.y)
			&& (m_mouseY <= rectangle.y + rectangle.h));
	}

	void MouseEvent::lock() {
		m_lockState = true;
	}

	void MouseEvent::unlock() {
		m_lockState = false;
	}

	void MouseEvent::clear() {
		m_mouseState.fill(0);
		m_scrollX = m_scrollY = 0;
		m_mouseMoveX = m_mouseMoveY = 0;
		m_mouse = SDL_GetMouseState(&m_mouseX, &m_mouseY);
	}

	void MouseEvent::set(int32_t x, int32_t y, int32_t moveX, int32_t moveY) {
		//clear();
		m_mouseX = x;
		m_mouseY = y;
		m_mouseMoveX = moveX;
		m_mouseMoveY = moveY;
	}

	void MouseEvent::set(uint8_t button, int32_t state) {
		//clear();
		m_mouseState[button] = static_cast<int8_t>(state);
	}

	void MouseEvent::set(int32_t scrollX, int32_t scrollY) {
		//clear();
		m_scrollX = scrollX;
		m_scrollY = scrollY;
	}
}