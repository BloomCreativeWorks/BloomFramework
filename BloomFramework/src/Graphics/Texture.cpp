#include "Graphics/Texture.h"
#include "Exception.h"

namespace bloom::graphics {
	Texture::Texture(SDL_Renderer* const& targetRenderer, const std::filesystem::path& filePath, std::optional<SDL_Color> colorKey) : Drawable(targetRenderer) {
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(filePath.u8string().c_str());
		if (!loadedSurface)
			throw Exception{ "Texture", SDL_GetError() };

		if (colorKey.has_value())
			SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));

		//Create texture from surface pixels
		m_texture = SDL_CreateTextureFromSurface(c_renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
		if (!m_texture)
			throw Exception{ "Texture", SDL_GetError() };
	}
}