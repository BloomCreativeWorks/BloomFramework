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

}