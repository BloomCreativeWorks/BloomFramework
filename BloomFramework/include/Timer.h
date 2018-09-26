#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		void start();
		void restart();
		double split();
		double lap();
		double totalTime();

	private:
		Uint64 m_startTicks = 0;
	};
}