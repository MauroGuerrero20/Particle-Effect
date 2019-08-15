#include "Swarm.h"
namespace mpgSDL {

Swarm::Swarm() : lastTime(0) { m_pParticles = new Particle[N_PARTICLES]; }

Swarm::~Swarm() { delete[] m_pParticles; }

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime;

  for (int i = 0; i < Swarm::N_PARTICLES; i++) {
    m_pParticles[i].update(interval);
  }

	lastTime = elapsed;

}
} // namespace mpgSDL