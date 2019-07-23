#pragma once
#include "stdIncludes.h"
#include <optional>

namespace bloom::graphics {
	class SpriteText;

	struct FontStyle {
		int pointSize = 20;
		int fontStyle = TTF_STYLE_NORMAL;
		int hinting = TTF_HINTING_NORMAL;
		int outlineWidth = 0;
		bool allowKerning = true;
	};

	class BLOOMFRAMEWORK_API Font {
		friend class SpriteText;

	public:
		Font(const std::filesystem::path& fontPath, int pointSize);
		Font(const std::filesystem::path& fontPath, int pointSize, long fontFaceIndex);
		Font(const std::filesystem::path& fontPath, const FontStyle& style = FontStyle{});
		~Font();

		std::string getFamilyName() const {
			const char* fontName = TTF_FontFaceFamilyName(m_font);
			return fontName ? std::string{ fontName } : std::string{};
		}

		std::string getStyleName() const {
			const char* fontStyle = TTF_FontFaceStyleName(m_font);
			return fontStyle ? std::string{ fontStyle } : std::string{};
		}

		int getPointSize() const {
			return m_style.pointSize;
		}

		bool isFixedWidth() const { // maybe `isMonospaced` is better?
			return TTF_FontFaceIsFixedWidth(m_font);
		}

	private:
        Font(const std::filesystem::path& fontPath, FontStyle style, std::optional<int> pointSize, std::optional<long> fontFaceIndex);

		operator TTF_Font*() const { return m_font; }

		TTF_Font* m_font = nullptr;
		FontStyle m_style;
	};

	using FontPtr = std::shared_ptr<Font>;
}