#pragma once

#include "stdIncludes.h"
#include <iostream>
#include "Game.h"
#include <fstream>
#include <string>

namespace BloomFramework {
	class BLOOMFRAMEWORK_API Map {
	public:
		Map();
		~Map();

		static void loadMap(Game* gameObject, std::string path, int sizeX, int sizeY);
	private:
	};
}