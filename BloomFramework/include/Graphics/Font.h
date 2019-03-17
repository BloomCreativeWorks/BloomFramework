#pragma once

#include "stdIncludes.h"
#include "Exception.h"

namespace bloom::graphics {
	struct TextStyle;
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

		std::string getFamilyName() const;
		std::string getStyle() const;
		int getPointSize() const { return m_style.pointSize; }
		bool isFixedWidth() const { return TTF_FontFaceIsFixedWidth(m_font); }

		//TTF_Font * getFont() const { return m_font; }

	private:
		void initFont();

		TTF_Font* m_font = nullptr;
		FontStyle m_style{};
	};

	using FontPtr = std::shared_ptr<Font>;
}