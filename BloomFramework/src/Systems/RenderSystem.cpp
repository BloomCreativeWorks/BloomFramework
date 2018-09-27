#include "Systems/RenderSystem.h"

namespace bloom {
	void RenderSystem::update(entt::DefaultRegistry & registry)
	{
		registry.view<Position, Size, Sprite>().each(
			[](auto entity, Position & pos, Size& size, Sprite & spr) {
			SDL_Rect destRect{
				static_cast<int>(pos.x),
				static_cast<int>(pos.x),
				static_cast<int>(size.w),
				static_cast<int>(size.h)
			};
				spr._texture->render(spr._srcRect, destRect);
		});
	}
}