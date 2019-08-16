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

		double split() const {
			return (static_cast<double>(SDL_GetPerformanceCounter() - m_timerTicks) / static_cast<double>(SDL_GetPerformanceFrequency() / 1000.0));
		}

		double lap() {
			const auto oldTicks = m_timerTicks;
			m_timerTicks = SDL_GetPerformanceCounter();
			return (static_cast<double>(m_timerTicks - oldTicks) / static_cast<double>(SDL_GetPerformanceFrequency() / 1000.0));
		}

		double objectLifetime() const {
			return (static_cast<double>(SDL_GetPerformanceCounter() - m_startTicks) / static_cast<double>(SDL_GetPerformanceFrequency() / 1000.0));
		}

	private:
		uint64_t m_startTicks, m_timerTicks;
	};
}