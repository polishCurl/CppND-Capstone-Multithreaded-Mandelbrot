#include "controller.h"

#include "SDL.h"
#include "mandelbrot.h"

void Controller::HandleInput(bool &running, Mandelbrot &mandelbrot) const {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        running = false;
        break;
      case SDLK_UP:
        mandelbrot.MoveUp();
        break;
      case SDLK_DOWN:
        mandelbrot.MoveDown();
        break;
      case SDLK_LEFT:
        mandelbrot.MoveLeft();
        break;
      case SDLK_RIGHT:
        mandelbrot.MoveRight();
        break;
      case SDLK_EQUALS:
        mandelbrot.ZoomIn();
        break;
      case SDLK_MINUS:
        mandelbrot.ZoomOut();
        break;
      case SDLK_PERIOD:
        mandelbrot.IncreaseAccuracy();
        break;
      case SDLK_COMMA:
        mandelbrot.DecreaseAccuracy();
        break;
      case SDLK_r:
        mandelbrot.ResetView();
        break;
      default:
        break;
      }
    } else if ((event.type == SDL_MOUSEBUTTONDOWN) &&
               (event.button.button == SDL_BUTTON_LEFT)) {
      mandelbrot.MoveToPoint(event.button.x, event.button.y);
      mandelbrot.ZoomIn();
    }
  }
}