#pragma once

#include "stdIncludes.h"
#include "Exception.h"

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
		int hinting = TTF_HINTING_NORMAL;
		SDL_Color foregroundColor = { 255, 255, 255, 0 };
		SDL_Color backGroundColor = { 0, 0, 0, 0 };
		BlendingMode blendingMode = normal;
	};

	static TextStyle defaultTextStyle = TextStyle();

	class BLOOMFRAMEWORK_API Font {
	public:
		Font(const std::filesystem::path & fontPath, int pointSize);
		Font(const std::filesystem::path & fontPath, int pointSize, long fontFaceIndex);
		~Font();

		std::string getFamilyName() const;
		std::string getStyle() const;
		int getPointSize() const { return m_pointSize; }
		bool isFixedWidth() const { return TTF_FontFaceIsFixedWidth(m_font); }

		SDL_Texture * createTexture(SDL_Renderer * renderer, const std::string & text, const TextStyle & style = defaultTextStyle);

		//SDL_Texture * operator()(SDL_Renderer *& renderer, std::string text, TextStyle style = TextStyle()) {
		//	return createTexture(renderer, text, style);
		//}

	private:
		TTF_Font * m_font = nullptr;
		int m_pointSize;
	};
}