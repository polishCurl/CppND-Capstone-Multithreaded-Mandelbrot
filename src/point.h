#ifndef POINT_H_
#define POINT_H_

#include <array>

struct RgbColor {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

class Point {
public:
  void SetColor(size_t iterations, size_t max_iter);
  RgbColor GetColor() const { return *color_; };

private:
  const RgbColor *color_;
  static const RgbColor kBlack_; // color reserved for the Mandelbrot set

  // maps iteration count to RGB color
  static const std::array<RgbColor, 16> kColorMap_;
};

#endif // POINT_H_