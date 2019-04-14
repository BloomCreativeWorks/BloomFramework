#pragma once

#include "stdIncludes.h"

namespace bloom {
	class Timer {
	public:
		Timer() : m_startTicks(SDL_GetPerformanceCounter()), m_timerTicks(m_startTicks) {}

		static uint32_t totalLifetime() {
			return SDL_GetTicks();
		}

		void restart() {
			m_timerTicks = SDL_GetPerformanceCounter();
		}

		[[deprecated("This function is deprecated. Use `restart()` instead")]]
		void start() {
			restart();
		}

		uint64_t split() const {
			return ((SDL_GetPerformanceCounter() - m_timerTicks) / (SDL_GetPerformanceFrequency() / 1000));
		}

		uint64_t lap() {
			const auto oldTicks = m_timerTicks;
			m_timerTicks = SDL_GetPerformanceCounter();
			return ((m_timerTicks - oldTicks) / (SDL_GetPerformanceFrequency() / 1000));
		}

		uint64_t objectLifetime() const {
			return ((SDL_GetPerformanceCounter() - m_startTicks) / (SDL_GetPerformanceFrequency() / 1000));
		}

	private:
		uint64_t m_startTicks, m_timerTicks;
	};
}