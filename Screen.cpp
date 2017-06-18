#include "Screen.h"

#include <memory>

namespace particlesim {
	
	Screen::Screen() :
		_window(nullptr), _render(nullptr), _texture(nullptr), _buffer1(nullptr), _buffer2(nullptr){
	}

	bool Screen::init(){
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		_window = SDL_CreateWindow("Particle Simulation",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (_window == nullptr) {
			SDL_Quit();
			return 2;
		}

		_render = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (_render == nullptr) {

			SDL_DestroyWindow(_window);
			SDL_Quit();
			return false;
		}

		_texture = SDL_CreateTexture(_render,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH, SCREEN_HEIGHT);

		if (_texture == nullptr) {

			SDL_DestroyWindow(_window);
			SDL_DestroyRenderer(_render);
			SDL_Quit();
			return false;
		}

		_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		memset(_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		return true;
	}

	bool Screen::processEvents(){
		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {

				return false;
			}
		}

		return true;
	}

	void Screen::boxBlur() {

		Uint32* temp = _buffer1;
		_buffer1 = _buffer2;
		_buffer2 = temp;

		for (int y = 0; y < SCREEN_HEIGHT-0; y++) {
			for (int x = 0; x < SCREEN_WIDTH-0; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
							Uint32 color = _buffer2[currentY*SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::clear() {
		memset(_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	}

	void Screen::close() {
		delete[] _buffer1;
		delete[] _buffer2;

		SDL_DestroyRenderer(_render);
		SDL_DestroyTexture(_texture);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		_buffer1[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::update() {
		SDL_UpdateTexture(_texture, nullptr, _buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(_render);
		SDL_RenderCopy(_render, _texture, nullptr, nullptr);
		SDL_RenderPresent(_render);
	}
}