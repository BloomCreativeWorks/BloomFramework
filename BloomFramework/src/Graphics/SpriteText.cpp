#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	SpriteText::SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr) : Drawable(targetRenderer) {
		m_loadedFontPtr = fontPtr;
	}

	void SpriteText::update() {
		m_texture = m_loadedFontPtr->createTexture(m_renderer, text, style);
	}

	void SpriteText::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		m_texture = m_loadedFontPtr->createTexture(m_renderer, text, style);
		Drawable::render(srcRect, destRect, flip);
	}
}