#include "point.h"

const RgbColor Point::kBlack_{0, 0, 0};

const std::array<RgbColor, 16> Point::kColorMap_ = {
    RgbColor{66, 30, 15},    // brown 3
    RgbColor{25, 7, 26},     // dark violett
    RgbColor{9, 1, 47},      // darkest blue
    RgbColor{4, 4, 73},      // blue 5
    RgbColor{0, 7, 100},     // blue 4
    RgbColor{12, 44, 138},   // blue 3
    RgbColor{24, 82, 177},   // blue 2
    RgbColor{57, 125, 209},  // blue 1
    RgbColor{134, 181, 229}, // blue 0
    RgbColor{211, 236, 248}, // lightest blue
    RgbColor{241, 233, 191}, // lightest yellow
    RgbColor{248, 201, 95},  // light yellow
    RgbColor{255, 170, 0},   // dirty yellow
    RgbColor{204, 128, 0},   // brown 0
    RgbColor{153, 87, 0},    // brown 1
    RgbColor{106, 52, 3}     // brown 2
};

void Point::SetColor(size_t iterations, size_t max_iter) {
  if ((iterations < max_iter) && (iterations != 0)) {
    color_ = &kColorMap_[iterations % kColorMap_.size()];
  } else {
    color_ = &kBlack_;
  }
}