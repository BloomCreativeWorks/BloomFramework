#pragma once
#include "stdIncludes.h"
#include <map>
#include "Texture.h"
#include <optional>

namespace bloom {
	typedef std::shared_ptr<Texture> TexturePtr;
	class BLOOMFRAMEWORK_API TextureStore {
	public:
		TextureStore(SDL_Renderer ** renderer);

		TexturePtr load(const std::string & filePath , std::optional<SDL_Color> colorKey = std::nullopt);
		TexturePtr getTexture(const std::string & filePath);
		void destroyTexture(const std::string & filePath);
 

	private:
		SDL_Renderer ** m_renderer;
		std::map<std::string, TexturePtr> m_store;
	};
}