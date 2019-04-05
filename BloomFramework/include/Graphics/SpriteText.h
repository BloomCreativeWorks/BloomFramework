#pragma once
#include "stdIncludes.h"
#include "Drawable.h"
#include "Font.h"

namespace bloom::graphics {
	struct TextStyle {
		enum class BlendingMode {
			normal = 0,
			shaded = 1,
			blended = 2
		} blendingMode = BlendingMode::normal;
		SDL_Color foregroundColor = { 255, 255, 255, 0 };
		SDL_Color backgroundColor = { 0, 0, 0, 0 };
	};

	class BLOOMFRAMEWORK_API SpriteText : public Drawable {
	public:
		SpriteText(SDL_Renderer* const& targetRenderer, std::shared_ptr<Font> fontPtr, std::string_view text = std::string_view{}, TextStyle style = TextStyle{});
		~SpriteText() = default;

		void render(std::optional<SDL_Rect> srcRect, SDL_Point destPoint, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int getTextHeight() const {
			return m_height;
		}

		int getTextWidth() const {
			return m_width;
		}

		std::string getText() const {
			return m_text;
		}

		void setText(std::string_view newText) {
			if (m_text != newText) {
				m_text = newText;
				m_refreshRequired = true;
			}
		}

		TextStyle getStyle() const {
			return m_style;
		}

		void setStyle(const TextStyle& newStyle) {
			m_style = newStyle;
			m_refreshRequired = true;
		}

	private:
		void refreshTexture();

		FontPtr m_fontPtr;
		int m_height = 0;
		int m_width = 0;

		std::string m_text;
		TextStyle m_style;

		bool m_refreshRequired = false;
	};
}