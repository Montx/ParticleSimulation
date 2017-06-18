#pragma once

namespace particlesim {

	class Particle {

	public:
		double x;
		double y;

	private:
		double _speed;
		double _direction;

	public:
		Particle();
		virtual ~Particle();

		void update(int interval);

	private:
		void init();
	};
}