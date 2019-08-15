#pragma once
#include "Particle.h"

namespace mpgSDL {
class Swarm {
public:
  const static int N_PARTICLES = 5000;

private:
  Particle *m_pParticles;
	int lastTime;

public:
  Swarm();
  virtual ~Swarm();
  void update(int elapsed);

  Particle *getParticles() { return m_pParticles; }
};
} // namespace mpgSDL
