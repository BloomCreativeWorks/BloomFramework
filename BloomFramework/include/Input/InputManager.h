#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputEvents.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		InputManager() noexcept = default;

		bool update(bool continueOnQuit = false);
		bool quitRequested() noexcept;
		void resetQuit() noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		//EventType getType() const noexcept;

		KeyboardEvent keyboard{};
		MouseEvent mouse{};
		
	private:
		void reset();

		bool m_quitState = false;
		EventType m_lastType = EventType::UnknownEvent;
		SDL_Event m_intlEvent;
		//bool m_lockState = false;
	};
}