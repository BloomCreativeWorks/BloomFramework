#pragma once

#include "stdIncludes.h"
#include <stack>

namespace bloom {
	class Scene;
	class BLOOMFRAMEWORK_API SceneManager {
	public:
		void changeScene(Scene * newScene);
		void update();
		void draw();

	private:
		Scene * currScene;
	};
}