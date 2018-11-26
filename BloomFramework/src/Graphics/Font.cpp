#include "Graphics/Font.h"
#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	Font::Font(const std::filesystem::path & fontPath, int pointSize) {
		if (!std::filesystem::exists(fontPath)) {
			throw Exception("[Font] font file not exists");
		}

		m_font = TTF_OpenFont(fontPath.u8string().c_str(), pointSize);
		m_style.pointSize = pointSize;
		TTF_SetFontStyle(m_font, m_style.fontStyle);
		TTF_SetFontHinting(m_font, m_style.hinting);
		TTF_SetFontKerning(m_font, static_cast<int>(m_style.allowKerning));
		TTF_SetFontOutline(m_font, m_style.outlineWidth);
	}

	Font::Font(const std::filesystem::path & fontPath, int pointSize, long fontFaceIndex) {
		if (!std::filesystem::exists(fontPath)) {
			throw Exception("[Font] font file not exists");
		}

		m_font = TTF_OpenFontIndex(fontPath.u8string().c_str(), pointSize, fontFaceIndex);
		m_style.pointSize = pointSize;
		TTF_SetFontStyle(m_font, m_style.fontStyle);
		TTF_SetFontHinting(m_font, m_style.hinting);
		TTF_SetFontKerning(m_font, static_cast<int>(m_style.allowKerning));
		TTF_SetFontOutline(m_font, m_style.outlineWidth);
	}

	Font::Font(const std::filesystem::path & fontPath, FontStyle style) : m_style(style) {
		if (!std::filesystem::exists(fontPath)) {
			throw Exception("[Font] font file not exists");
		}

		m_font = TTF_OpenFont(fontPath.u8string().c_str(), m_style.pointSize);
		TTF_SetFontStyle(m_font, m_style.fontStyle);
		TTF_SetFontHinting(m_font, m_style.hinting);
		TTF_SetFontKerning(m_font, static_cast<int>(m_style.allowKerning));
		TTF_SetFontOutline(m_font, m_style.outlineWidth);
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
}