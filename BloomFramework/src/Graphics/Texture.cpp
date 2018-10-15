#include "Graphics/Texture.h"
#include "Exception.h"

namespace bloom::graphics {
	Texture::Texture(SDL_Texture * texture, SDL_Renderer *& target_renderer) : texture_(texture), renderer_(target_renderer) {}

	void Texture::render(std::optional<SDL_Rect> src_rect, SDL_Rect dest_rect, SDL_RendererFlip flip) {
		if (dest_rect.w <= 0)
			throw Exception("[Texture Render] destcRect.w is <= 0.\nIs that intentional?");
		if (dest_rect.h <= 0)
			throw Exception("[Texture Render] destRect.h is <= 0.\nIs that intentional?");
		if (src_rect.has_value()) {
			if (src_rect->w <= 0)
				throw Exception("[Texture Render] srcRect.w is <= 0.\nIs that intentional?");
			if (src_rect->h <= 0)
				throw Exception("[Texture Render] srcRect.h is <= 0.\nIs that intentional?");

			//Set rendering space and render to screen
			//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

			//Render to screen
			SDL_RenderCopyEx(renderer_, texture_, &src_rect.value(), &dest_rect, 0.0, nullptr, flip);
		}
		else {
			//Render to screen
			SDL_RenderCopyEx(renderer_, texture_, nullptr, &dest_rect, 0.0, nullptr, flip);
		}
	}

	Texture::~Texture() {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}
