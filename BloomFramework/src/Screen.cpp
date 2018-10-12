#include "Screen.h"
#include "Game.h"

namespace bloom {
	Screen::Screen(Game * gameInstance) : m_gameInstance(gameInstance) {
		m_createTexture();
	}

	Screen::~Screen() {
		for (auto& gameObj : m_gameObjects)
			gameObj.second->~GameObject();
	}

	void Screen::update() {
		m_createTexture();
		SDL_SetRenderTarget(m_gameInstance->getRenderer(), m_screenTexture);
		double dt = m_gameInstance->timer.lap();
		for (auto& sys : m_systems)
			sys->update(dt);
		std::cout << "Delta Time: " << dt << "ms" << std::endl;
	}
	void Screen::destroyGameObject(std::string tag) {
		m_gameObjects.erase(tag);
	}
	SDL_Texture *& Screen::getScreenTexture()
	{
		return m_screenTexture;
	}
	void Screen::m_createTexture()
	{
		if (!m_screenTexture)
			SDL_DestroyTexture(m_screenTexture);

		m_screenTexture = SDL_CreateTexture(m_gameInstance->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			m_gameInstance->getScreenWidth(),
			m_gameInstance->getScreenHeight());

		SDL_SetTextureBlendMode(m_screenTexture, SDL_BLENDMODE_BLEND);
	}
}