#pragma once

namespace BloomFramework {
	/// <summary>
	/// This is a type used to store loaded SDL_Surfaces
	/// </summary>
	class BLOOMFRAMEWORK_API TextureStore {
	public:
		/// <summary>
		/// Initializes the type and sets the destinationSurface to the SDL_Surface given.
		/// </summary>
		/// <param name="destinationSurface">Target SDL_Surface</param>
		TextureStore(SDL_Surface* destinationSurface) : TargetScreen(destinationSurface) {}

		/// <summary>
		/// Loads a texture from the given path and optimizes it to the destination surface.
		/// </summary>
		/// <param name="path">Path to image file</param>
		/// <param name="nickname">
		/// Nickname for given texture.
		/// If none is given, the path will be used instead.
		/// </param>
		/// <returns>True if successfully loaded image, false otherwise.</returns>
		bool loadTexture(std::string path, std::string nickname = "");

		/// <summary>
		/// Retrieve a surface with the requested texture.
		/// </summary>
		/// <param name="nickname">Nickname given to texture when loading.</param>
		/// <returns>A surface with the requested texture.</returns>
		SDL_Surface* getTexture(std::string nickname);
	private:
		std::vector<std::pair<std::string,SDL_Surface*>> storage;
		SDL_Surface* TargetScreen;
		bool optimize = false;
	};
}
