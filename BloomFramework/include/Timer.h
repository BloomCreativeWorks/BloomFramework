#pragma once

#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer();

		static Uint32 totalLifetime();

		void start();
		void restart();
		double split();
		double lap();
		double objectLifetime();

	private:
		Uint64	m_startTicks, m_timerTicks;
	};
}