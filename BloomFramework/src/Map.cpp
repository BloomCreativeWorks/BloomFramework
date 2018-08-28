#include "../inc/Map.h"

BloomFramework::Map::Map() {}

BloomFramework::Map::~Map() {}

void BloomFramework::Map::loadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	for(int y = 0; y < sizeY; y++) {
		for(int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}
	mapFile.close();
}


