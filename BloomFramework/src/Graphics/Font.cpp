#include "Graphics/Font.h"

namespace bloom::graphics {
	Font::Font(const std::filesystem::path & fontPath, int pointSize) {
		if (!std::filesystem::exists(fontPath)) {
			throw Exception("[Font] font file not exists");
		}

		m_font = TTF_OpenFont(fontPath.u8string().c_str(), pointSize);
		m_pointSize = pointSize;
	}

	Font::Font(const std::filesystem::path & fontPath, int pointSize, long fontFaceIndex) {
		if (!std::filesystem::exists(fontPath)) {
			throw Exception("[Font] font file not exists");
		}

		m_font = TTF_OpenFontIndex(fontPath.u8string().c_str(), pointSize, fontFaceIndex);
		m_pointSize = pointSize;
	}

	Font::~Font() {
		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}

	std::string Font::getFamilyName() const {
		char * fontName = TTF_FontFaceFamilyName(m_font);
		if (fontName) {
			return std::string(fontName);
		}
		else {
			return "";
		}
	}

	std::string Font::getStyle() const {
		char * fontStyle = TTF_FontFaceStyleName(m_font);
		if (fontStyle) {
			return std::string(fontStyle);
		}
		else {
			return "";
		}
	}

	SDL_Texture * Font::createTexture(SDL_Renderer * renderer, const std::string & text, const TextStyle & style) {
		SDL_Surface * textSurface = nullptr;
		if (TTF_GetFontStyle(m_font) != style.fontStyle)
			TTF_SetFontStyle(m_font, style.fontStyle);
		if (TTF_GetFontHinting(m_font) != style.hinting)
			TTF_SetFontHinting(m_font, style.hinting);
		if (TTF_GetFontKerning(m_font) != static_cast<int>(style.allowKerning))
			TTF_SetFontKerning(m_font, static_cast<int>(style.allowKerning));
		if (TTF_GetFontOutline(m_font) != style.outlineWidth)
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
			if (!texture) {
				throw Exception("[Font -> SDL_Texture] " + std::string(SDL_GetError()));
			}
			else {
				return texture;
			}
		}
	}
}