#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	SpriteText::SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr) : Drawable(targetRenderer) {
		m_loadedFontPtr = fontPtr;
		update();
	}

	void SpriteText::update() {
		SDL_DestroyTexture(m_texture);
		m_texture = m_loadedFontPtr->createTexture(m_renderer, text, style);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
	}
}