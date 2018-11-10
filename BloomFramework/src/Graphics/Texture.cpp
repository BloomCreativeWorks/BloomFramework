#include "Graphics/Texture.h"
#include "Exception.h"

namespace bloom::graphics {
	Texture::Texture(SDL_Renderer *& targetRenderer, const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey) : m_renderer(targetRenderer) {
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

	void Texture::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		if (destRect.w <= 0)
			throw Exception("[Texture::render] destcRect.w is <= 0.\nIs that intentional?");
		if (destRect.h <= 0)
			throw Exception("[Texture::render] destRect.h is <= 0.\nIs that intentional?");

		if (srcRect.has_value()) {
			if (srcRect->w <= 0)
				throw Exception("[Texture::render] srcRect.w is <= 0.\nIs that intentional?");
			if (srcRect->h <= 0)
				throw Exception("[Texture::render] srcRect.h is <= 0.\nIs that intentional?");

			//Set rendering space and render to screen
			//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, &srcRect.value(), &destRect, 0.0, nullptr, flip);
		}
		else
			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &destRect, 0.0, nullptr, flip);
	}

	Texture::~Texture() {
		SDL_DestroyTexture(m_texture);
	}
}
