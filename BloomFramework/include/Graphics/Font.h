#pragma once
#include "stdIncludes.h"

namespace bloom::graphics {
	struct TextStyle {
		enum BlendingMode {
			normal = 0,
			shaded = 1,
			blended = 2
		};

		int fontStyle = TTF_STYLE_NORMAL;
		int outlineWidth = 0;
		bool allowKerning = true;
		int hinting = TTF_HINTING_NONE;
		SDL_Color foregroundColor = { 255, 255, 255, 0 };
		SDL_Color backGroundColor = { 0, 0, 0, 0 };
		BlendingMode blendingMode = normal;
	};

	class BLOOMFRAMEWORK_API Font {
	public:
		Font(const std::filesystem::path & fontPath, int pointSize);
		Font(const std::filesystem::path & fontPath, int pointSize, long fontFaceIndex);
		~Font();

		std::string getFontName();
		std::string getFontStyle();
		int getPointSize();
		bool isFixedWidth() { return TTF_FontFaceIsFixedWidth(m_font); }

		SDL_Texture * createTexture(SDL_Renderer *& renderer, std::string text, TextStyle style = TextStyle());

	private:
		TTF_Font * m_font = nullptr;
		int m_pointSize;
	};
}