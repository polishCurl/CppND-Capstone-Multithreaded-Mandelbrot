#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <atomic>
#include <complex>
#include <thread>
#include <vector>

#include "barrier.h"
#include "point.h"

typedef std::vector<std::vector<Point>> Points;

class Mandelbrot {
public:
  Mandelbrot(size_t width, size_t height, size_t thread_count);
  ~Mandelbrot();

  // complete 'The Rule of Five'
  Mandelbrot(const Mandelbrot &) = delete;
  Mandelbrot(Mandelbrot &&) = delete;
  Mandelbrot &operator=(const Mandelbrot &) = delete;
  Mandelbrot &operator=(Mandelbrot &&) = delete;

  unsigned char GetPixelRed(size_t x, size_t y) const { return points_[y][x].GetColor().r; }
  unsigned char GetPixelGreen(size_t x, size_t y) const {return points_[y][x].GetColor().g; }
  unsigned char GetPixelBlue(size_t x, size_t y) const { return points_[y][x].GetColor().b; }

  size_t GetIterationLimit() const { return iter_limit_; }
  std::complex<float> GetCameraCenter() const { return center_; }

  void ZoomIn() { zoom_ *= kZoomMultiplier_; };
  void ZoomOut() { zoom_ /= kZoomMultiplier_; };
  void MoveUp() {center_ = {center_.real(), center_.imag() - (kMoveSpeed_ * kZoomMultiplier_)}; }
  void MoveDown() { center_ = {center_.real(), center_.imag() + (kMoveSpeed_ * kZoomMultiplier_)}; }
  void MoveLeft() { center_ = {center_.real() - (kMoveSpeed_ * kZoomMultiplier_), center_.imag()}; }
  void MoveRight() { center_ = {center_.real() + (kMoveSpeed_ * kZoomMultiplier_), center_.imag()}; }
  void MoveToPoint(size_t x, size_t y) { center_ = PixelToComplexNumber(x, y); }

  void IncreaseAccuracy() { if (iter_limit_ < kIterLimitMax_) iter_limit_++; }
  void DecreaseAccuracy() { if (iter_limit_ > kIterLimitMin_) iter_limit_--; }

  // mandelbrot computation is asynchronous to the main program loop
  void Launch() { workers_ready_->Wait(); };
  void WaitForCompletion() { workers_done_->Wait(); }

  void ResetView();

private:
  void RunWorkerThread(int thread_id, size_t thread_count);
  size_t IterationsToDiverge(size_t x, size_t y) const;
  std::complex<float> PixelToComplexNumber(size_t x, size_t y) const;

  Points points_;
  float zoom_;                 // the smaller the value the bigger the zoom
  std::complex<float> center_; // center of the 'camera' points here

  size_t iter_limit_;

  const size_t kWidth_;
  const size_t kHeight_;

  std::vector<std::thread> workers_;
  std::unique_ptr<Barrier> workers_done_;
  std::unique_ptr<Barrier> workers_ready_;
  std::atomic<bool> terminate_workers_{false};

  static constexpr float kZoomStart_ = 0.005;
  static constexpr float kRealCenterStart_ = -0.76;
  static constexpr float kImagCenterStart_ = 0;
  static constexpr size_t kIterLimitStart_ = 32;
  static constexpr size_t kIterLimitMin_ = 1;
  static constexpr size_t kIterLimitMax_ = 256;
  static constexpr float kZoomMultiplier_ = 0.9;
  static constexpr float kMoveSpeed_ = 0.0025;
  static constexpr size_t kIterationMultiplier_ = 2;
};

#endif // MANDELBROT_H_