#include "Graphics/Font.h"
namespace bloom::graphics {
	Font::Font(const std::filesystem::path &  fontPath, int pointSize) {
		m_font = TTF_OpenFont(fontPath.u8string().c_str(), pointSize);
		m_pointSize = pointSize;
	}

	Font::Font(const std::filesystem::path &  fontPath, int pointSize, long fontFaceIndex) {
		m_font = TTF_OpenFontIndex(fontPath.u8string().c_str(), pointSize, fontFaceIndex);
		m_pointSize = pointSize;
	}

	Font::~Font() {
		TTF_CloseFont(m_font);
	}

	std::string Font::getFontName() {
		char * fontName = TTF_FontFaceFamilyName(m_font);
		if (fontName == nullptr) {
			return "Unavailable";
		}
		else {
			return fontName;
		}
	}
	std::string Font::getFontStyle() {
		char * fontStyle = TTF_FontFaceFamilyName(m_font);
		if (fontStyle == nullptr) {
			return "Unavailable";
		}
		else {
			return fontStyle;
		}
	}

	int Font::getPointSize() {
		return m_pointSize;
	}

	SDL_Texture * Font::createTexture(SDL_Renderer *& renderer, std::string text, TextStyle style) {
		SDL_Surface * textSurface = nullptr;

		TTF_SetFontStyle(m_font, style.fontStyle);
		if (TTF_GetFontHinting(m_font) != style.hinting)
			TTF_SetFontHinting(m_font, style.hinting);
		TTF_SetFontKerning(m_font, static_cast<int>(style.allowKerning));
		TTF_SetFontOutline(m_font, style.outlineWidth);

		switch (style.blendingMode) {
		case style.normal:
			textSurface = TTF_RenderUTF8_Solid(m_font, text.c_str(), style.foregroundColor);
			break;
		case style.shaded:
			textSurface = TTF_RenderUTF8_Shaded(m_font, text.c_str(), style.foregroundColor, style.backGroundColor);
			break;
		case style.blended:
			textSurface = TTF_RenderUTF8_Blended(m_font, text.c_str(), style.foregroundColor);
			break;
		}
		if (textSurface == nullptr) {
			throw Exception("[Font -> TTF_RenderUTF8] " + std::string(SDL_GetError()));
		}
		else {
			SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_FreeSurface(textSurface);
			if (texture == nullptr) {
				throw Exception("[Font -> SDL_Texture] " + std::string(SDL_GetError()));
			}
			else {
				return texture;
			}
		}
	}
}