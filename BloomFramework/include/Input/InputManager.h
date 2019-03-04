#pragma once

#include <array>
#include "stdIncludes.h"
/// All keys are defined here.
#include "InputEvents.h"

namespace bloom::input {
	class BLOOMFRAMEWORK_API InputManager {
	public:
		InputManager() noexcept = default;

		void update();
		bool quitRequested() noexcept;
		void lock() noexcept;
		void unlock() noexcept;
		EventType getType() const noexcept;

		KeyboardEvent keyboard{};
		MouseEvent mouse{};
		
	private:
		void reset();

		EventType m_type = EventType::UnknownEvent;
		//bool m_lockState = false;
	};
}