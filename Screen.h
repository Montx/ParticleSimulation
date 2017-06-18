#pragma once

#include "SDL_includes.h"

namespace particlesim {

	class Screen {

	public:
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;

	private:
		SDL_Window* _window;
		SDL_Renderer* _render;
		SDL_Texture* _texture;

		Uint32* _buffer1;
		Uint32* _buffer2;

	public:
		Screen();

		bool init();
		bool processEvents();

		void boxBlur();
		void clear();
		void close();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
	};
}
