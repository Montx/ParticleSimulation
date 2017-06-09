#pragma once

namespace particlesim {

	class Particle {

	private:
		double m_x;
		double m_y;

	public:
		Particle();
		virtual ~Particle();
	};
}