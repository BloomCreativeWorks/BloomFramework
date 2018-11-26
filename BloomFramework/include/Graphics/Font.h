#pragma once

#include "stdIncludes.h"
#include "Exception.h"

namespace bloom::graphics {
	struct TextStyle;

	struct FontStyle {
		int pointSize = 20;
		int fontStyle = TTF_STYLE_NORMAL;
		int hinting = TTF_HINTING_NORMAL;
		int outlineWidth = 0;
		bool allowKerning = true;
	};

	static FontStyle defaultFontStyle = FontStyle();

	class BLOOMFRAMEWORK_API Font {
	public:
		Font(const std::filesystem::path & fontPath, int pointSize);
		Font(const std::filesystem::path & fontPath, int pointSize, long fontFaceIndex);
		Font(const std::filesystem::path & fontPath, FontStyle style = defaultFontStyle);
		~Font();

		std::string getFamilyName() const;
		std::string getStyle() const;
		int getPointSize() const { return m_style.pointSize; }
		bool isFixedWidth() const { return TTF_FontFaceIsFixedWidth(m_font); }

		TTF_Font * getFont() const {
			return m_font;
		}

	private:
		TTF_Font * m_font = nullptr;
		FontStyle m_style = defaultFontStyle;
	};

	using FontPtr = std::shared_ptr<Font>;
}