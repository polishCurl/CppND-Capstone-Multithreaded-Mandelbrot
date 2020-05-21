#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "mandelbrot.h"

class Controller {
public:
  void HandleInput(bool &running, Mandelbrot &mandelbrot) const;
};

#endif // CONTROLLER_H_