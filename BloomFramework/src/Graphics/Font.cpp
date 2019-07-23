#include "Exception.h"
#include "Graphics/Font.h"
#include "Graphics/SpriteText.h"

namespace bloom::graphics {
    Font::Font(const std::filesystem::path& fontPath, FontStyle style, std::optional<int> pointSize, std::optional<long> fontFaceIndex) :
        m_style(style)
    {
        if (!std::filesystem::exists(fontPath))
            throw Exception{ "Font", "Font file doesn't exist" };

        if (pointSize)
            m_style.pointSize = pointSize.value();

        if (fontFaceIndex)
            m_font = TTF_OpenFontIndex(fontPath.u8string().c_str(), pointSize.value_or(m_style.pointSize), fontFaceIndex.value());
        else
            m_font = TTF_OpenFont(fontPath.u8string().c_str(), pointSize.value_or(m_style.pointSize));

        if (!m_font)
            throw Exception{ "Font", TTF_GetError() };

        TTF_SetFontStyle(m_font, m_style.fontStyle);
        TTF_SetFontHinting(m_font, m_style.hinting);
        TTF_SetFontKerning(m_font, static_cast<int>(m_style.allowKerning));
        TTF_SetFontOutline(m_font, m_style.outlineWidth);
    }

	Font::Font(const std::filesystem::path& fontPath, int pointSize) :
        Font(fontPath.u8string().c_str(), FontStyle{}, pointSize, std::nullopt)
    {}

	Font::Font(const std::filesystem::path& fontPath, int pointSize, long fontFaceIndex) :
        Font(fontPath.u8string().c_str(), FontStyle{}, pointSize, fontFaceIndex)
    {}

    Font::Font(const std::filesystem::path& fontPath, const FontStyle& style) :
        Font(fontPath.u8string().c_str(), style, std::nullopt, std::nullopt)
    {}

    Font::~Font() {
		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}
}