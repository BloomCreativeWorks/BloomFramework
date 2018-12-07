#include "stdIncludes.h"

#include "Timer.h"

namespace bloom {
	Timer::Timer() noexcept : m_startTicks(SDL_GetPerformanceCounter()), m_timerTicks(m_startTicks) {}

	Uint32 Timer::totalLifetime() noexcept {
		return SDL_GetTicks();
	}

	void Timer::start() noexcept {
		m_timerTicks = SDL_GetPerformanceCounter();
	}

	void Timer::restart() noexcept {
		start();
	}

	double Timer::split() const noexcept {
		return (static_cast<double>(SDL_GetPerformanceCounter() - m_timerTicks) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	double Timer::lap() noexcept {
		const Uint64 oldTicks = m_timerTicks;
		m_timerTicks = SDL_GetPerformanceCounter();
		return (static_cast<double>(m_timerTicks - oldTicks) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	double Timer::objectLifetime() const noexcept {
		return (static_cast<double>(SDL_GetPerformanceCounter() - m_startTicks) * 1000.0 / SDL_GetPerformanceFrequency());
	}
}