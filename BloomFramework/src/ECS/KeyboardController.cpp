#include "..\..\inc\ECS\KeyboardController.h"

inline void BloomFramework::KeyboardController::init() {
	transform = &entity->getComponent<TransformComponent>();
	sprite = &entity->getComponent<SpriteComponent>();
}

inline void BloomFramework::KeyboardController::update() {
	if(gameObject->event.type == SDL_KEYDOWN) {
		switch(gameObject->event.key.keysym.sym) {
		case SDLK_w:
			transform->velocity.y = -1;
			sprite->play("Walk");
			break;
		case SDLK_s:
			transform->velocity.y = 1;
			sprite->play("Walk");
			break;
		case SDLK_a:
			transform->velocity.x = -1;
			sprite->play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_d:
			transform->velocity.x = 1;
			sprite->play("Walk");
			sprite->spriteFlip = SDL_FLIP_NONE;
			break;
		default:
			break;
		}
	}

	if(gameObject->event.type == SDL_KEYUP) {
		switch(gameObject->event.key.keysym.sym) {
		case SDLK_w:
			transform->velocity.y = 0;
			sprite->play("Idle");
			break;
		case SDLK_s:
			transform->velocity.y = 0;
			sprite->play("Idle");
			break;
		case SDLK_a:
			transform->velocity.x = 0;
			sprite->play("Idle");
			break;
		case SDLK_d:
			transform->velocity.x = 0;
			sprite->play("Idle");
			break;
		default:
			break;
		}
	}
}
