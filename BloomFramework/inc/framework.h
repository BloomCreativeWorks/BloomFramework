#pragma once
#ifdef BLOOMFRAMEWORK_EXPORT
#define BLOOMFRAMEWORK_API __declspec(dllexport) 
#else 
#define BLOOMFRAMEWORK_API __declspec(dllimport) 
#endif

//Using SDL and standard IO
#include <SDL.h>
#undef main
#include <stdio.h>

namespace BloomFramework {
	class BLOOMFRAMEWORK_API GraphicsWindow {
	public:
		void initWindow();

	private:
		//Screen dimension constants
		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT = 480;
	};
}
