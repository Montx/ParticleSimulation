#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace particlesim {

	static const double M_PI = 3.14159265358979323846;

	Particle::Particle() {

		init();
	}

	void Particle::init() {
		x = 0;
		y = 0;

		_direction = (2 * M_PI *  rand()) / RAND_MAX;
		_speed = (0.04 * rand()) / RAND_MAX;

		_speed *= _speed;
	}

	Particle::~Particle() {
		
	}

	void Particle::update(int interval) {

		_direction += interval * 0.0003;

		double xspeed = _speed * cos(_direction);
		double yspeed = _speed * sin(_direction);

		x += xspeed * interval;
		y += yspeed * interval;

		if (x < -1 || x > 1 || y < -1 || y > 1) {
			init();
		}

		if (rand() < RAND_MAX / 100) {
			init();
		}
	}
}