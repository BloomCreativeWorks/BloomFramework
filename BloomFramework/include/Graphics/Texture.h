#pragma once

#include <optional>
#include "stdIncludes.h"
#include "IDrawable.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Texture : public IDrawable  {
	public:
		explicit Texture(SDL_Renderer *& targetRenderer, const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
	};

	using TexturePtr = std::shared_ptr<Texture>;
}