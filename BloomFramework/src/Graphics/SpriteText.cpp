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
		refreshTexture();
	}

	void SpriteText::render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip) {
		if (text != m_previousText)
			refreshTexture();
		SDL_Rect destRect{ destPoint.x, destPoint.y, m_width, m_height };
		Drawable::render(srcRect, destRect, flip);
	}

	void SpriteText::refreshTexture() {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

		SDL_Surface * textSurface = nullptr;

		switch (style.blendingMode) {
		case TextStyle::normal:
			textSurface = TTF_RenderUTF8_Solid(m_fontPtr->m_font, text.c_str(), style.foregroundColor);
			break;
		case TextStyle::shaded:
			textSurface = TTF_RenderUTF8_Shaded(m_fontPtr->m_font, text.c_str(), style.foregroundColor, style.backGroundColor);
			break;
		case TextStyle::blended:
			textSurface = TTF_RenderUTF8_Blended(m_fontPtr->m_font, text.c_str(), style.foregroundColor);
			break;
		}
		if (textSurface == nullptr) {
			throw Exception("[Font -> TTF_RenderUTF8] " + std::string(SDL_GetError()));
		}
		else {
			m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
			SDL_FreeSurface(textSurface);
			if (!m_texture) {
				throw Exception("[Font -> SDL_Texture] " + std::string(SDL_GetError()));
			}

			SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
		}

		m_previousText = text;
	}
}