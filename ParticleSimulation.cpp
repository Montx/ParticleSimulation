#include <iostream>

#include <math.h>
#include "SDL_includes.h"

#include "Screen.h"

using namespace particlesim;

int main(int argc, char *args[]) {

	Screen screen;
	
	if (!screen.init()) {
		std::cout << "Error initialising SDL!" << std::endl;
	}

	while (true) {
		// Update particles
		// Draw particles

		int elapsed = SDL_GetTicks();

		// Unsigned char to make sure the value is not 256
		unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				screen.setPixel(x, y, red, green, blue);
			}
		}

		// Draw the screen
		screen.update();

		// Check for messages/events
		if (!screen.processEvents()) {
			break;
		}

	}

	screen.close();
	
    return 0;
}

