#include "Particle.h"
#include <SDL_stdinc.h>
#include <math.h>
#include <stdlib.h>

namespace mpgSDL {

Particle::Particle() {

  // Cartesian Coordinate System

  // Return a random number b/w 1 and -1;
  // m_x = ((2.0 * rand()) / RAND_MAX) - 1;
  // m_y = ((2.0 * rand()) / RAND_MAX) - 1;

  // m_xspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
  // m_yspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);

  // Polar Coordinate System
	init();

}

void Particle::init() {

	m_x = 0;
	m_y = 0;

	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;

	m_speed *= m_speed;

}

Particle::~Particle() {}

void Particle::update(int interval) {

  // Cartesian Coordinates System

  // m_x += m_xspeed;
  // m_y += m_yspeed;

  // if (m_x < -1 || m_x >= 1)
  //  m_xspeed = -m_xspeed;

  // if (m_y < -1 || m_y >= 1)
  //  m_yspeed = -m_yspeed;

	m_direction += interval * 0.0004;

  double xspeed = m_speed * cos(m_direction);
  double yspeed = m_speed * sin(m_direction);

  m_x += xspeed * interval;
  m_y += yspeed * interval;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if (rand() < RAND_MAX / 100) {
		init();
	}

}
} // namespace mpgSDL
