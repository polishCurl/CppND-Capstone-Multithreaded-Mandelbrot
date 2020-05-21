#include "barrier.h"

Barrier::Barrier(size_t thread_count)
    : total_threads_(thread_count), count_(thread_count), cycle_(0) {}

void Barrier::Wait() {
  std::unique_lock<std::mutex> u_lock{mutex_};
  auto last_cycle = cycle_;

  if (--count_ == 0) {
    cycle_++;
    count_ = total_threads_;
    condition_.notify_all();

  } else {
    condition_.wait(u_lock,
                    [this, last_cycle] { return last_cycle != cycle_; });
  }
}