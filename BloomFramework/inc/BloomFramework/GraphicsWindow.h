#pragma once

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
		bool loadMedia(const std::string imagePath);
		/// <summary>
		/// Load an image onto the surface.
		/// </summary>
		/// <param name="texture">Memory address of preloaded texture</param>
		/// <returns>Return true when image loading succeeded, false otherwise.</returns>
		bool loadMedia(SDL_Surface* texture);

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

		// The window we'll be rendering to
		SDL_Window* gWindow = NULL;

		// The surface contained by the window
		SDL_Surface* gScreenSurface = NULL;

		SDL_Surface* gImage = NULL;

	private:
		std::string WINDOW_TITLE = "Undefined";

		int SCREEN_WIDTH = 640;
		int SCREEN_HEIGHT = 480;
		int SCREEN_X_POS = SDL_WINDOWPOS_UNDEFINED;
		int SCREEN_Y_POS = SDL_WINDOWPOS_UNDEFINED;


	};
}