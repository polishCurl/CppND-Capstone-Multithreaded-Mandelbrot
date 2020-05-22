#include "mandelbrot.h"

#include <algorithm>

Mandelbrot::Mandelbrot(size_t width, size_t height, size_t thread_count)
    : kWidth_(width), kHeight_(height) {

  for (size_t y = 0; y < height; y++) {
    std::vector<Point> row(width);
    points_.emplace_back(row);
  }

  ResetView();

  // the two barriers synchronize all worker threads and this (calling) thread
  workers_ready_ = std::make_unique<Barrier>(thread_count + 1);
  workers_done_ = std::make_unique<Barrier>(thread_count + 1);

  for (size_t i = 0; i < thread_count; i++) {
    workers_.emplace_back(
        std::thread(&Mandelbrot::RunWorkerThread, this, i, thread_count));
  }
}

Mandelbrot::~Mandelbrot() {
  terminate_workers_ = true;

  std::for_each(workers_.begin(), workers_.end(),
                [](std::thread &t) { t.join(); });
}

void Mandelbrot::ResetView() {
  zoom_ = kZoomStart_;
  center_ = {kRealCenterStart_, kImagCenterStart_};
  iter_limit_ = kIterLimitStart_;
}

void Mandelbrot::RunWorkerThread(int thread_id, size_t thread_count) {
  while (true) {
    workers_ready_->Wait();

    for (size_t y = thread_id; y < kHeight_; y += thread_count) {
      for (size_t x = 0; x < kWidth_; x++) {
        points_[y][x].SetColor(IterationsToDiverge(x, y), iter_limit_);
      }
    }

    if (terminate_workers_.load())
      return;

    workers_done_->Wait();
  }
}

size_t Mandelbrot::IterationsToDiverge(size_t x, size_t y) const {
  std::complex<float> c = PixelToComplexNumber(x, y);
  std::complex<float> z(0, 0);

  size_t iterations = 0;

  while ((abs(z) < 2) && (iterations++ < iter_limit_)) {
    z = z * z + c;
  }

  return iterations;
}

std::complex<float> Mandelbrot::PixelToComplexNumber(size_t x, size_t y) const {
  float x_f = x;
  float y_f = y;
  float width_f = kWidth_;
  float height_f = kHeight_;

  float real = center_.real() + (x_f - (width_f / 2)) * zoom_;
  float imag = center_.imag() + (y_f - (height_f / 2)) * zoom_;

  return {real, imag};
}