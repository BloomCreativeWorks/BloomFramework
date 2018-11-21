#pragma once

#include "stdIncludes.h"
#include "Texture.h"
#include "Exception.h"
#include "Font.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API SpriteText : public Drawable {
	public:
		SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr);
		void update();

		int getTextHeight() { return m_height; }
		int getTextWidth() { return m_width; }
		void changeText(std::string newText) { text = newText; update(); }

		std::string text = "Unitialized";
		TextStyle style;

	private:
		std::shared_ptr<Font> m_loadedFontPtr;
		int m_height = 0;
		int m_width = 0;
	};
}