#include <iostream>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "SDL_includes.h"
#include "Screen.h"
#include "Swarm.h"

using namespace particlesim;

int main(int argc, char *args[]) {

	// Random Seed
	srand(time(nullptr));

	Screen screen;
	
	if (!screen.init()) {
		std::cout << "Error initialising SDL!" << std::endl;
	}

	Swarm swarm;

	while (true) {

		int elapsed = SDL_GetTicks();

		// Update particles
		//screen.clear();
		swarm.update(elapsed);

		// Draw particles

		// Unsigned char to make sure the value is not 256
		unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		const Particle* const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

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

