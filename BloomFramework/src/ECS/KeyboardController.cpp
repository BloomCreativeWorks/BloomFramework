#include "..\..\inc\ECS\KeyboardController.h"

inline void BloomFramework::KeyboardController::init() {
	transform = &entity->getComponent<TransformComponent>();
}

inline void BloomFramework::KeyboardController::update() {
	if(Game::event.type == SDL_KEYDOWN) {
		switch(Game::event.key.keysym.sym) {
		case SDLK_w:
			transform->velocity.y = -1;
			break;
		case SDLK_s:
			transform->velocity.y = 1;
			break;
		case SDLK_a:
			transform->velocity.x = -1;
			break;
		case SDLK_d:
			transform->velocity.x = 1;
			break;
		default:
			break;
		}
	}

	if(Game::event.type == SDL_KEYUP) {
		switch(Game::event.key.keysym.sym) {
		case SDLK_w:
			transform->velocity.y = 0;
			break;
		case SDLK_s:
			transform->velocity.y = 0;
			break;
		case SDLK_a:
			transform->velocity.x = 0;
			break;
		case SDLK_d:
			transform->velocity.x = 0;
			break;
		default:
			break;
		}
	}
}
