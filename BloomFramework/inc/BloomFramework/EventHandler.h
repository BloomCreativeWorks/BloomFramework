#pragma once

namespace BloomFramework {
	enum BLOOMFRAMEWORK_API Events {
		quit = 256,
		empty,
		up,
		down,
		left,
		right
	};
	class BLOOMFRAMEWORK_API EventHandler {
	public:
		/// <summary>
		/// Get input from
		/// </summary>
		/// <returns>Returns an event for processing</returns>
		Events getInput();
	private:
		SDL_Event e;
	};
}
