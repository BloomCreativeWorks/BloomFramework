#include "../inc/Map.h"
int test[20][25] = { 
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1},
	{2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},
	{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},
	{1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1}
};

BloomFramework::Map::Map() {
	dirt = TextureManager::loadTexture("assets/dirt.png");
	grass = TextureManager::loadTexture("assets/grass.png");
	water = TextureManager::loadTexture("assets/water.png");

	loadMap(test);
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = 32;
	srcRect.h = destRect.h = 32;
}

BloomFramework::Map::~Map() {}

void BloomFramework::Map::loadMap(int levelMap[20][25]) {
	for(int row = 0; row < 20; row++) {
		for(int col = 0; col < 25; col++) {
			map[row][col] = levelMap[row][col];
		}
	}
}

void BloomFramework::Map::drawMap() {
	int type = 0;
	for(int row = 0; row < 20; row++) {
		for(int col = 0; col < 25; col++) {
			type = map[row][col];
			destRect.x = col * 32;
			destRect.y = row * 32;
			switch(type) {
			case 0:
				TextureManager::draw(water, srcRect, destRect);
				break;
			case 1:
				TextureManager::draw(grass, srcRect, destRect);
				break;
			case 2:
				TextureManager::draw(dirt, srcRect, destRect);
				break;

			default:
				break;
			}
		}
	}
}
