#ifndef RENDERER_H_
#define RENDERER_H_

#include "SDL.h"
#include "mandelbrot.h"

class Renderer {
public:
  Renderer(size_t width, size_t height);
  ~Renderer();

  // complete 'The Rule of Five'
  Renderer(const Renderer &) = delete;
  Renderer(Renderer &&) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void Render(const Mandelbrot &mandelbrot);
  void UpdateWindowTitle(size_t fps, size_t iter_bound,
                         std::complex<float> center);

private:
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;

  const size_t kScreenWidth_;
  const size_t kScreenHeight_;
};

#endif // RENDERER_H_