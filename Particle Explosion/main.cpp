#include "Screen.h"
#include "Swarm.h"
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace mpgSDL;

int main(int argc, char *argv[]) {

  srand(time(NULL));

  Screen screen;

  if (screen.init() == false)
    cout << "Initialization error." << endl;

  Swarm swarm;

  while (true) {
    // Update Particles

    // Draw Particles

    int elapsed = SDL_GetTicks();

    swarm.update(elapsed);

    unsigned int red = (1 + cos(elapsed * 0.0003)) * 128;
    unsigned int green = (1 + sin(elapsed * 0.0002)) * 128;
    unsigned int blue = (1 + cos(elapsed * 0.0001)) * 128;

    const Particle const *pParticles = swarm.getParticles();

    for (int i = 0; i < Swarm::N_PARTICLES; i++) {

      Particle particle = pParticles[i];

      int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH / 2);
      int y = (particle.m_y * Screen::SCREEN_WIDTH / 2) +
              (Screen::SCREEN_HEIGHT / 2);

      screen.setPixel(x, y, red, green, blue);
    }

    screen.boxBlur();

    // Draw the screen
    screen.update();

    // Check for messages/events
    if (screen.processEvents() == false)
      break;
  }

  screen.close();

  return EXIT_SUCCESS;
}