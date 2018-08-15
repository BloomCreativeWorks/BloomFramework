#pragma once
#ifdef BLOOMFRAMEWORK_EXPORT
#define BLOOMFRAMEWORK_API __declspec(dllexport)
#else
#define BLOOMFRAMEWORK_API __declspec(dllimport)
#endif

// Using SDL and standard IO
#include <SDL.h>
#undef main
#include <iostream>
#include <string>
#include <stdio.h>

namespace BloomFramework {
	/// <summary>
	/// Graphics window container.
	/// </summary>
	class BLOOMFRAMEWORK_API GraphicsWindow {
	public:
		/// <summary>
		/// Initialize graphics window with preset title, size, and position..
		/// </summary>
		/// <returns>Return true when initialization succeeded, false otherwise.</returns>
		bool initWindow();

		/// <summary>
		/// Load an image onto the surface.
		/// </summary>
		/// <param name="imagePath">Path to the image file.</param>
		/// <returns>Return true when image loading succeeded, false otherwise.</returns>
		bool loadMedia(std::string imagePath);

		/// <summary>
		/// Updates the window.
		/// </summary>
		void updateWindow();

		/// <summary>
		/// Destroy graphics window.
		/// </summary>
		void destroyWindow();

		/// <summary>
		/// Sets the title to be displayed in title bar.
		/// </summary>
		/// <param name="title">String to be used as title.</param>
		void setWindowTitle(std::string title);

		/// <summary>
		/// Sets window width.
		/// </summary>
		/// <param name="width">Value(in pixels) to be used as the width of the window.</param>
		void setWidth(int width);

		/// <summary>
		/// Sets window height.
		/// </summary>
		/// <param name="height">Value(in pixels) to be used as the height of the window.</param>
		void setHeight(int height);

		/// <summary>
		/// Sets window X position.
		/// </summary>
		/// <param name="xPosition">Coordinates(in pixels) from the left to be used as the position of the window.</param>
		void setXPos(int xPosition);

		/// <summary>
		/// Sets window Y position
		/// </summary>
		/// <param name="yPosition">Coordinates(in pixels) from the left to be used as the position of the window.</param>
		void setYPos(int yPosition);

	private:
		std::string WINDOW_TITLE = "Undefined";

		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT = 480;
		int SCREEN_X_POS = SDL_WINDOWPOS_UNDEFINED;
		int SCREEN_Y_POS = SDL_WINDOWPOS_UNDEFINED;

		// The window we'll be rendering to
		SDL_Window* gWindow = NULL;

		// The surface contained by the window
		SDL_Surface* gScreenSurface = NULL;

		// The image we will load and show on the screen
		SDL_Surface* gImage = NULL;
	};

	enum BLOOMFRAMEWORK_API Events {
		quit = 256,
		empty,
		up,
		down,
		left,
		right
	};

	class BLOOMFRAMEWORK_API InputHandler {
	public:
		/// <summary>
		/// Get input from
		/// </summary>
		/// <returns>Returns an event for processing</returns>
		Events getInput();
	private:
		SDL_Event e;
	};
} // namespace BloomFramework
