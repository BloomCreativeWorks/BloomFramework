#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputEvents.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		bool update(bool continueOnQuit = false);
		// If timeout < 0, the function will wait for the event indefinitely
		EventType wait(int timeout = -1);
		bool quitRequested() noexcept;

		void lock() noexcept;
		void unlock() noexcept;

		KeyboardEvent keyboard{};
		MouseEvent mouse{};
		
	private:
		void reset();
		void handle();

		bool m_quitState = false;
		SDL_Event m_intlEvent{};
		EventType m_lastType = EventType::NoEvent;
	};
}