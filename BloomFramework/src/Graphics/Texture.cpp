#include "Graphics/Texture.h"
#include "Exception.h"

namespace bloom::graphics {
	Texture::Texture(SDL_Renderer *& targetRenderer, const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey) : IDrawable(targetRenderer) {
		//Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(filePath.u8string().c_str());
		if (loadedSurface == nullptr) {
			throw Exception("[Texture -> SDL_IMG] " + std::string(SDL_GetError()));
		}
		else {
			if (colorKey.has_value())
				SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));
			//Create texture from surface pixels
			m_texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
			if (m_texture == nullptr) {
				throw Exception("[Texture -> SDL_Texture] " + std::string(SDL_GetError()));
			}
			SDL_FreeSurface(loadedSurface);
		}
	}
}
