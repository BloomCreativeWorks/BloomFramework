#pragma once

#include "export.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer();

		static Uint32 totalLifetime();

		void start();
		void restart();
		double split() const;
		double lap();
		double objectLifetime() const;

	private:
		Uint64	m_startTicks, m_timerTicks;
	};
}