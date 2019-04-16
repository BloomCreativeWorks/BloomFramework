#pragma once
#include <optional>
#include "stdIncludes.h"
#include "Drawable.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Texture : public Drawable {
	public:
		explicit Texture(SDL_Renderer* const& targetRenderer, const std::filesystem::path& filePath, std::optional<SDL_Color> colorKey = std::nullopt);
	};

	using TexturePtr = std::shared_ptr<Texture>;
}