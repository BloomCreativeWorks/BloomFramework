#include "..\..\inc\ECS\TileComponent.h"

BloomFramework::TileComponent::TileComponent(int x, int y, int w, int h, int id) {
	tileRect.x = x;
	tileRect.y = y;
	tileRect.w = w;
	tileRect.h = h;
	tileID = id;

	switch(tileID) {
	case 0:
		path= (char*) "assets/water.png";
		break;
	case 1:
		path = (char*) "assets/dirt.png";
		break;
	case 2:
		path = (char*) "assets/grass.png";
		break;
	default: break;
	}
}

void BloomFramework::TileComponent::init() {
	entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
	transform = &entity->getComponent<TransformComponent>();

	entity->addComponent<SpriteComponent>(path);
	sprite = &entity->getComponent<SpriteComponent>();
}
