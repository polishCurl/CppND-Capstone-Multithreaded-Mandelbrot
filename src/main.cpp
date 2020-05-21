#include <thread>

#include "mandelbrot_viewer.h"

int main() {
  size_t threads = std::thread::hardware_concurrency();
  MandelbrotViewer mandelbrot_viewer(640, 640, threads);
  mandelbrot_viewer.Run();
  return 0;
}