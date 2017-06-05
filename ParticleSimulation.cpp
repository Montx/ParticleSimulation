#include <iostream>

#include "SDL_includes.h"

#include "Screen.h"


int main(int argc, char *args[]) {

	particleSim::Screen screen;
	
	if (!screen.init()) {
		std::cout << "Error initialising SDL!" << std::endl;
	}

	bool running = true;

	SDL_Event event;

	while (running) {
		// Update particles
		// Draw particles
		// Check for messages/events

		if (!screen.processEvents()) {
			break;
		}

	}

	screen.close();
	
    return 0;
}

