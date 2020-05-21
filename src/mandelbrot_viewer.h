#ifndef MANDELBROT_VIEWER_H_
#define MANDELBROT_VIEWER_H_

#include "controller.h"
#include "mandelbrot.h"
#include "renderer.h"

class MandelbrotViewer {
public:
  MandelbrotViewer(size_t width, size_t height, size_t threads = 1);
  void Run();

private:
  Renderer renderer_;
  Controller controller_;
  Mandelbrot mandelbrot_;
};

#endif // MANDELBROT_VIEWER_H_