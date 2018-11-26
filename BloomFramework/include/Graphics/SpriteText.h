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
		SDL_Color backGroundColor = { 0, 0, 0, 0 };
	};

	static TextStyle defaultTextStyle = TextStyle();

	class BLOOMFRAMEWORK_API SpriteText : public Drawable {
	public:
		SpriteText(SDL_Renderer *& targetRenderer, std::shared_ptr<Font> fontPtr, std::string text = " ", TextStyle style = defaultTextStyle);
		~SpriteText() = default;

		void refreshTexture();
		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) override;
		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int getTextHeight() const { return m_height; }
		int getTextWidth() const { return m_width; }
		void changeText(const std::string & newText) { text = newText; refreshTexture(); }

		std::string text;
		TextStyle style;

	private:
		FontPtr m_fontPtr;
		int m_height = 0;
		int m_width = 0;
	};
}