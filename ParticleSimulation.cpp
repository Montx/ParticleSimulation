#include <iostream>

#include <SDL.h>


int main(int argc, char *args[])
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL Init failed" << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Particle Simulation", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit();
		return 2;
	}

	bool running = true;

	while (running) {
		// Update particles
		// Draw particles
		// Check for messages/events

		while (SDL_PollEvents()) {

		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}

