#pragma once

#include "Particle.h"

namespace particlesim {

	class Swarm {
	public:
		const static int NPARTICLES = 5000;

	private:
		Particle* _particles;
		int lastTime;

	public:
		Swarm();
		virtual ~Swarm();

		const Particle* const getParticles() { return _particles; };

		void update(int elapsed);
	};
}