#pragma once

#include "stdIncludes.h"
#include "Texture.h"
#include "Exception.h"
#include "Font.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API SpriteText : public Drawable {
	public:
		SpriteText(SDL_Renderer *& targetRenderer,	std::shared_ptr<Font> fontPtr);
		void update();

		std::string text = "Unitialized";
		TextStyle style;
		
	private:
		std::shared_ptr<Font> m_loadedFontPtr;
	};
}