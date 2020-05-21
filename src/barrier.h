#ifndef BARRIER_H_
#define BARRIER_H_

#include <condition_variable>
#include <mutex>

// reusable thread synchronization barrier
class Barrier {
public:
  explicit Barrier(size_t thread_count);
  void Wait();

private:
  std::mutex mutex_;
  std::condition_variable condition_;
  size_t total_threads_;
  size_t count_; // counts down threads required to release barrier
  size_t cycle_;
};

#endif // BARRIER_H_