#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	SpriteText::SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr, std::string text, TextStyle style) :
		Drawable(targetRenderer),
		m_fontPtr(fontPtr),
		text(text),
		style(style)
	{
		if (text.empty()) {
			std::cerr << "[SpriteText] the use of an empty string is not allowed" << std::endl;
			std::clog << "[SpriteText] the empty string will be replaced with a space" << std::endl;
			text += ' ';
		}
		m_texture = m_fontPtr->createTexture(m_renderer, text, style);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
	}

	void SpriteText::refresh() {
		SDL_DestroyTexture(m_texture);
		if (text.empty()) {
			std::cerr << "[SpriteText] the use of an empty string is not allowed" << std::endl;
			std::clog << "[SpriteText] the empty string will be replaced with a space" << std::endl;
			text += ' ';
		}
		m_texture = m_fontPtr->createTexture(m_renderer, text, style);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
	}

	void SpriteText::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		Drawable::render(srcRect, destRect, flip);
	}

	void SpriteText::render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip) {
		SDL_Rect destRect{ destPoint.x, destPoint.y, m_width, m_height };
		Drawable::render(srcRect, destRect, flip);
	}
}