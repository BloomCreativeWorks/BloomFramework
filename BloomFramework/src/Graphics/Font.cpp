#include "Exception.h"
#include "Graphics/Font.h"
#include "Graphics/SpriteText.h"

namespace bloom::graphics {
	Font::Font(const std::filesystem::path& fontPath, int pointSize) {
		if (!std::filesystem::exists(fontPath))
			throw Exception{ "Font", "Font file doesn't exist" };

		m_font = TTF_OpenFont(fontPath.u8string().c_str(), pointSize);
		if (!m_font)
			throw Exception{ "Font", TTF_GetError() };
		m_style.pointSize = pointSize;
		initFont();
	}

	Font::Font(const std::filesystem::path& fontPath, int pointSize, long fontFaceIndex) {
		if (!std::filesystem::exists(fontPath))
			throw Exception{ "Font", "Font file doesn't exist" };

		m_font = TTF_OpenFontIndex(fontPath.u8string().c_str(), pointSize, fontFaceIndex);
		if (!m_font)
			throw Exception{ "Font", TTF_GetError() };
		m_style.pointSize = pointSize;
		initFont();
	}

	Font::Font(const std::filesystem::path& fontPath, const FontStyle& style) : m_style(style) {
		if (!std::filesystem::exists(fontPath))
			throw Exception{ "Font", "Font file doesn't exist" };

		m_font = TTF_OpenFont(fontPath.u8string().c_str(), m_style.pointSize);
		if (!m_font)
			throw Exception{ "Font", TTF_GetError() };
		initFont();
	}

	Font::~Font() {
		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}

	void Font::initFont() {
		TTF_SetFontStyle(m_font, m_style.fontStyle);
		TTF_SetFontHinting(m_font, m_style.hinting);
		TTF_SetFontKerning(m_font, static_cast<int>(m_style.allowKerning));
		TTF_SetFontOutline(m_font, m_style.outlineWidth);
	}
}