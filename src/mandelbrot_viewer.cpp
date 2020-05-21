#include "mandelbrot_viewer.h"

#include <cassert>

MandelbrotViewer::MandelbrotViewer(size_t width, size_t height, size_t threads)
    : renderer_(width, height), controller_(),
      mandelbrot_(width, height, threads) {

  assert(width != 0);
  assert(height != 0);
  assert(threads != 0);
}

void MandelbrotViewer::Run() {
  size_t title_timestamp = SDL_GetTicks();
  size_t frame_end;
  size_t frame_count = 0;
  bool running = true;
  mandelbrot_.Launch();

  while (running) {
    mandelbrot_.WaitForCompletion();
    controller_.HandleInput(running, mandelbrot_);
    renderer_.Render(mandelbrot_);
    mandelbrot_.Launch();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer_.UpdateWindowTitle(frame_count, mandelbrot_.GetIterationLimit(),
                                  mandelbrot_.GetCameraCenter());
      frame_count = 0;
      title_timestamp = frame_end;
    }
  }
}