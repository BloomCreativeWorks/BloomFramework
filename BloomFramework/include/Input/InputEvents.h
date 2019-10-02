#pragma once

#include "stdIncludes.h"
#include <bitset>
#include "InputDefinitions.h"
#include "Components/Position.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager;

	enum class EventType {
		NoEvent,
		QuitEvent,
		KeyboardEvent,
		MouseEvent,
		UnknownEvent
	};

	class BLOOMFRAMEWORK_API KeyboardEvent {
		friend class InputManager;

	public:
		KeyboardEvent() noexcept;

		bool wasDown(KeyboardKey key) const noexcept;
		bool wasUp(KeyboardKey key) const noexcept;

		bool isPressed(KeyboardKey key) const noexcept;
		bool stateChanged(KeyboardKey key) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		bool shift() const noexcept;
		bool ctrl() const noexcept;
		bool alt() const noexcept;
		bool capsLock() const noexcept;
		char toChar() const;

		operator char() const {
			return toChar();
		}

		class SymRecorder {
			friend class KeyboardEvent;
			
		public:
			void start() noexcept;
			std::string stop();
			void clear();
			void cancel();
			std::string transfer();
			const std::string& get() const;
			
		private:
			void append(char sym);
			
			bool m_state{ false };
			std::string m_str{};
		} recorder{};

	private:
		void reset();
		void set(const SDL_KeyboardEvent& kbe) noexcept;
		static bool isPrintable(SDL_Keycode key) noexcept;
		void updateModKeys();

		std::bitset<static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)> m_keyboard{};
		std::bitset<static_cast<size_t>(KeyboardKey::KEYBOARD_SIZE)> m_stateChanged{};
		char m_char{'\0'};

		bool m_lockState = false;
	};

	class BLOOMFRAMEWORK_API MouseEvent {
		friend class InputManager;

	public:
		using Coordinates = components::Position;

		MouseEvent() noexcept;

		bool wasDown(MouseButton button) const noexcept;
		bool wasUp(MouseButton button) const noexcept;

		uint8_t isPressed(MouseButton button) const noexcept;
		bool stateChanged(MouseButton button) const noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		int getX() const noexcept;
		int getY() const noexcept;
		Coordinates getPos() const noexcept;
		Coordinates getOffset() const noexcept;
		Coordinates getScroll() const noexcept;
		bool isInside(const SDL_Rect& rectangle) const noexcept;

	private:
		void reset() noexcept;
		void set(const SDL_MouseButtonEvent& mbe) noexcept;
		void set(const SDL_MouseMotionEvent& mme) noexcept;
		void set(const SDL_MouseWheelEvent& mwe) noexcept;

		std::array<uint8_t, static_cast<size_t>(MouseButton::MOUSE_SIZE)> m_mouse{};
		std::bitset<static_cast<size_t>(MouseButton::MOUSE_SIZE)> m_stateChanged{ 0 };

		Coordinates m_pos{ 0, 0 },
			m_offset{ 0, 0 },
			m_scroll{ 0, 0 };

		bool m_lockState = false;
	};
}
