#include "Screen.h"

namespace mpgSDL {

Screen::Screen()
    : m_window(nullptr), m_renderer(nullptr), m_texture(nullptr),
      m_buffer1(nullptr), m_buffer2(nullptr) {}

bool Screen::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    cout << "SDL is not Initialized" << SDL_GetError() << endl;
    return false;
  }

  m_window = SDL_CreateWindow("Particle Fire Explosion",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (m_window == nullptr) {
    cout << "Window error: " << SDL_GetError() << endl;
    SDL_QUIT;
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

  m_texture =
      SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888,
                        SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (m_renderer == nullptr) {
    cout << "Renderer error: " << SDL_GetError() << endl;
    SDL_DestroyWindow(m_window);
    SDL_QUIT;
    return false;
  }

  if (m_texture == nullptr) {
    cout << "Texture error: " << SDL_GetError() << endl;
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_QUIT;
    return false;
  }

  m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

  memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}

bool Screen::processEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      return false;
  }
  return true;
}

void Screen::boxBlur() {

  Uint32 *temp = m_buffer1;
  m_buffer1 = m_buffer2;
  m_buffer2 = temp;

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {

      /*
      0 0 0
      0 1 0
      0 0 0
      */

      int redTotal = 0;
      int greenTotal = 0;
      int blueTotal = 0;

      for (int row = -1; row <= 1; row++) {
        for (int col = -1; col <= 1; col++) {

          int currentX = x + col;
          int currentY = y + row;

          if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 &&
              currentY < SCREEN_HEIGHT) {

            Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

            Uint8 red = color >> 16;
            Uint8 green = color >> 8;
            Uint8 blue = color;

            redTotal += red;
            greenTotal += green;
            blueTotal += blue;
          }
        }
      }

      Uint8 red = redTotal / 9;
      Uint8 green = greenTotal / 9;
      Uint8 blue = blueTotal / 9;

      setPixel(x, y, red, green, blue);
    }
  }
}

void Screen::close() {
  delete[] m_buffer1;
  delete[] m_buffer2;
  SDL_DestroyTexture(m_texture);
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_QUIT;
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    return;

  const char ALPHA = 0xFF;
  Uint32 color = 0;

  color += ALPHA;
  color <<= 8;
  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;

  m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

} // namespace mpgSDL
