#include "renderer.h"

#include <iostream>
#include <sstream>

Renderer::Renderer(size_t width, size_t height)
    : kScreenWidth_(width), kScreenHeight_(height) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window_ =
      SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

void Renderer::Render(const Mandelbrot &mandelbrot) {
  SDL_Event e;
  SDL_PollEvent(&e);

  for (size_t y = 0; y < kScreenHeight_; y++) {
    for (size_t x = 0; x < kScreenWidth_; x++) {
      SDL_SetRenderDrawColor(sdl_renderer_, mandelbrot.GetPixelRed(x, y),
                             mandelbrot.GetPixelGreen(x, y),
                             mandelbrot.GetPixelBlue(x, y), SDL_ALPHA_OPAQUE);

      SDL_RenderDrawPoint(sdl_renderer_, x, y);
    }
  }

  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle(size_t fps, size_t iter_bound,
                                 std::complex<float> center) {
  constexpr size_t kSpacing = 4;
  std::stringstream title;

  title << "FPS: " << fps << std::string(kSpacing, ' ')
        << "Iters: " << iter_bound << std::string(kSpacing, ' ')
        << "Center: " << center.real() << " + " << center.imag() << "i";

  SDL_SetWindowTitle(sdl_window_, title.str().c_str());
}