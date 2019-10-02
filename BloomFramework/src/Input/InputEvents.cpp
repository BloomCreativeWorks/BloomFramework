#include "Input/InputEvents.h"

namespace bloom::input {
	constexpr bool checkKey(bool lockState, KeyboardKey key) { return !lockState && key != KeyboardKey::KEYBOARD_SIZE; }

	constexpr bool checkButton(bool lockState, MouseButton button) { return !lockState && button != MouseButton::MOUSE_SIZE; }

	constexpr bool isLockKey(SDL_Scancode key) {
		return key == SDL_SCANCODE_CAPSLOCK || key == SDL_SCANCODE_NUMLOCKCLEAR || key == SDL_SCANCODE_SCROLLLOCK;
	}


	KeyboardEvent::KeyboardEvent() noexcept {
		int numKeys = 0;
		const auto kb = SDL_GetKeyboardState(&numKeys);
		const size_t keys = std::min(static_cast<size_t>(numKeys), m_keyboard.size());
		for (size_t i = 0; i < keys; ++i) {
			m_keyboard.set(i, kb[i]);
		}
		updateModKeys();
	}

	bool KeyboardEvent::wasDown(KeyboardKey key) const noexcept {
		return (isPressed(key) && m_stateChanged[static_cast<size_t>(key)]);
	}

	bool KeyboardEvent::wasUp(KeyboardKey key) const noexcept {
		return (!isPressed(key) && m_stateChanged[static_cast<size_t>(key)]);
	}

	bool KeyboardEvent::isPressed(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key)
			&& m_keyboard[static_cast<size_t>(key)]);
	}

	bool KeyboardEvent::stateChanged(KeyboardKey key) const noexcept {
		return (checkKey(m_lockState, key)
			&& m_stateChanged[static_cast<size_t>(key)]);
	}

	void KeyboardEvent::lock() noexcept {
		m_lockState = true;
	}

	void KeyboardEvent::unlock() noexcept {
		m_lockState = false;
	}

	bool KeyboardEvent::shift() const noexcept {
		return (isPressed(KeyboardKey::LShift) || isPressed(KeyboardKey::RShift));
	}

	bool KeyboardEvent::ctrl() const noexcept {
		return (isPressed(KeyboardKey::LCtrl) || isPressed(KeyboardKey::RCtrl));
	}

	bool KeyboardEvent::alt() const noexcept {
		return (isPressed(KeyboardKey::LAlt) || isPressed(KeyboardKey::RAlt));
	}

	bool KeyboardEvent::capsLock() const noexcept {
		return isPressed(KeyboardKey::CapsLock);
	}

	bool KeyboardEvent::isPrintable(SDL_Keycode key) noexcept {
		return (key >= SDLK_SPACE && key <= SDLK_z || key == SDLK_RETURN || key == SDLK_BACKSPACE);
	}

	void KeyboardEvent::updateModKeys() {
		const auto mod = SDL_GetModState();
		m_keyboard.set(SDL_SCANCODE_CAPSLOCK, mod & KMOD_CAPS);
		m_keyboard.set(SDL_SCANCODE_NUMLOCKCLEAR, mod & KMOD_NUM);
	}

	char KeyboardEvent::toChar() const {
		return m_char;
	}

	void KeyboardEvent::reset() {
		m_char = '\0';
		updateModKeys();
		m_stateChanged.reset();
	}

	void KeyboardEvent::set(const SDL_KeyboardEvent& kbe) noexcept {
		if (isLockKey(kbe.keysym.scancode)) {
			if (kbe.state) {
				m_keyboard.flip(kbe.keysym.scancode);
				m_stateChanged.set(kbe.keysym.scancode);
			}
		}
		else {
			if (static_cast<bool>(kbe.state) != m_keyboard[kbe.keysym.scancode])
				m_stateChanged.set(kbe.keysym.scancode);
			m_keyboard.set(kbe.keysym.scancode, kbe.state);
		}
		if (kbe.state && isPrintable(kbe.keysym.sym)) {
			m_char = static_cast<char>(kbe.keysym.sym);
			if ((shift() || capsLock()) && kbe.keysym.sym >= SDLK_a && kbe.keysym.sym <= SDLK_z)
				m_char -= ('a' - 'A');
			recorder.append(m_char);
		}
	}

	void KeyboardEvent::SymRecorder::start() noexcept { m_state = true; }

	void KeyboardEvent::SymRecorder::cancel() { m_state = false; m_str.clear(); }

	std::string KeyboardEvent::SymRecorder::transfer() { return std::move(m_str); }

	const std::string& KeyboardEvent::SymRecorder::get() const { return m_str; }

	std::string KeyboardEvent::SymRecorder::stop() { m_state = false; return std::move(m_str); }

	void KeyboardEvent::SymRecorder::clear() { m_str.clear(); }

	void KeyboardEvent::SymRecorder::append(char sym) {
		if (m_state) {
			switch (sym) {
			case '\0':
				break;
			case '\r': case '\n':
				m_str += "\r\n";
			case '\b':
				if (!m_str.empty())
					m_str.pop_back();
				break;
			default:
				m_str.push_back(sym);
			}
		}
	}


	MouseEvent::MouseEvent() noexcept {
		const auto mouseState = SDL_GetMouseState(nullptr, nullptr);
		for (size_t i = 1; i <= 3; ++i) {
			m_mouse[i] = mouseState & SDL_BUTTON(i);
		}
	}

	bool MouseEvent::wasDown(MouseButton button) const noexcept {
		return (isPressed(button) && m_stateChanged[static_cast<size_t>(button)]);
	}

	bool MouseEvent::wasUp(MouseButton button) const noexcept {
		return (!isPressed(button) && m_stateChanged[static_cast<size_t>(button)]);
	}

	uint8_t MouseEvent::isPressed(MouseButton button) const noexcept {
		if (checkButton(m_lockState, button))
			return m_mouse[static_cast<size_t>(button)];
		return 0;
	}

	bool MouseEvent::stateChanged(MouseButton button) const noexcept {
		return (checkButton(m_lockState, button)
			&& m_stateChanged[static_cast<size_t>(button)]);
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

	bool MouseEvent::isInside(const SDL_Rect& rectangle) const noexcept {
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
		m_stateChanged.reset();
		m_scroll.x = m_scroll.y = m_offset.x = m_offset.y = 0;
	}

	void MouseEvent::set(const SDL_MouseButtonEvent& mbe) noexcept {
		if (static_cast<bool>(m_mouse[mbe.button]) != static_cast<bool>(mbe.state))
			m_stateChanged.set(mbe.button);
		m_mouse[mbe.button] = mbe.state ? mbe.clicks : 0;
		m_pos.x = mbe.x; m_pos.y = mbe.y;
	}

	void MouseEvent::set(const SDL_MouseMotionEvent& mme) noexcept {
		m_pos.x = mme.x; m_pos.y = mme.y;
		m_offset.x = mme.xrel; m_offset.y = mme.yrel;
	}

	void MouseEvent::set(const SDL_MouseWheelEvent& mwe) noexcept {
		m_scroll.x = mwe.x; m_scroll.y = mwe.y;
	}
}