#pragma once

#include "stdIncludes.h"
#include "Exception.h"
#include "Drawable.h"
#include "Font.h"

namespace bloom::graphics {
	struct TextStyle {
		enum BlendingMode {
			normal = 0,
			shaded = 1,
			blended = 2
		} blendingMode = normal;
		SDL_Color foregroundColor = { 255, 255, 255, 0 };
		SDL_Color backgroundColor = { 0, 0, 0, 0 };

		bool operator==(const TextStyle& rhs) {
			bool foregroundSame = this->foregroundColor.a == rhs.foregroundColor.a
				&& this->foregroundColor.r == rhs.foregroundColor.r
				&& this->foregroundColor.g == rhs.foregroundColor.g
				&& this->foregroundColor.b == rhs.foregroundColor.b;

			bool backgroundSame = this->backgroundColor.a == rhs.backgroundColor.a
				&& this->backgroundColor.r == rhs.backgroundColor.r
				&& this->backgroundColor.g == rhs.backgroundColor.g
				&& this->backgroundColor.b == rhs.backgroundColor.b;

			return (this->blendingMode == rhs.blendingMode && foregroundSame && backgroundSame);
		}
		bool operator!=(const TextStyle& rhs) {
			return !(*this == rhs);
		}
	};

	static TextStyle defaultTextStyle = TextStyle();

	class BLOOMFRAMEWORK_API SpriteText : public Drawable {
	public:
		SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr, std::string text = " ", TextStyle style = defaultTextStyle);
		~SpriteText() = default;

	
		void render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int getTextHeight() const { return m_height; }
		int getTextWidth() const { return m_width; }

		std::string text;
		TextStyle style;

	private:
		void m_refreshTexture();

		FontPtr m_fontPtr;
		int m_height = 0;
		int m_width = 0;
		std::string m_previousText;
		TextStyle m_previousStyle;
	};
}