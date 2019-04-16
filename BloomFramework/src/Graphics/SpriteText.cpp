#include "Exception.h"
#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	SpriteText::SpriteText(SDL_Renderer* const& targetRenderer, std::shared_ptr<Font> fontPtr, std::string_view text, TextStyle style) :
		Drawable(targetRenderer),
		m_fontPtr(std::move(fontPtr)),
		m_text(text),
		m_style(style)
	{
		refreshTexture();
	}

	void SpriteText::render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip) {
		if (m_refreshRequired)
			refreshTexture();

		if (m_texture)
			Drawable::render(srcRect, SDL_Rect{ destPoint.x, destPoint.y, m_width, m_height }, flip);
	}

	void SpriteText::refreshTexture() {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}

		if (m_text.empty()) {
			m_width = m_height = 0;
			return;
		}

		SDL_Surface* textSurface = nullptr;

		switch (m_style.blendingMode) {
		case TextStyle::BlendingMode::normal:
			textSurface = TTF_RenderUTF8_Solid(*m_fontPtr, m_text.c_str(), m_style.foregroundColor);
			break;
		case TextStyle::BlendingMode::shaded:
			textSurface = TTF_RenderUTF8_Shaded(*m_fontPtr, m_text.c_str(), m_style.foregroundColor, m_style.backgroundColor);
			break;
		case TextStyle::BlendingMode::blended:
			textSurface = TTF_RenderUTF8_Blended(*m_fontPtr, m_text.c_str(), m_style.foregroundColor);
			break;
		}
		if (!textSurface)
			throw Exception{ "SpriteText::refreshTexture", TTF_GetError() };
		m_texture = SDL_CreateTextureFromSurface(c_renderer, textSurface);
		SDL_FreeSurface(textSurface);
		if (!m_texture)
			throw Exception{ "SpriteText::refreshTexture", SDL_GetError() };
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

		m_refreshRequired = false;
	}
}