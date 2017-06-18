#include "Swarm.h"

namespace particlesim {

	Swarm::Swarm() : lastTime(0) {
		_particles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm() {
		delete[] _particles;
	}

	void Swarm::update(int elapsed) {

		int interval = elapsed - lastTime;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			_particles[i].update(interval);
		}

		lastTime = elapsed;
	}
}