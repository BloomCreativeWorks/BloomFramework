#pragma once

#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() : m_startTicks(SDL_GetPerformanceCounter()), m_timerTicks(m_startTicks) {}

		void start();
		void restart();
		double split();
		double lap();
		double objectLifetime();
		static Uint32 totalLifetime();

	private:
		Uint64	m_startTicks, m_timerTicks;
	};
}