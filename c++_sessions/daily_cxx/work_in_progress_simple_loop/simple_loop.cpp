#include <chrono>  // high_resolution_clock, duration_cast
#include <cstdint> // int8_t int32_t
#include <cstdio>  // printf
#include <tuple>
#include <vector>

class Timer {
  using Time = decltype(::std::chrono::high_resolution_clock::now());

  Time BeginTime;
  Time EndTime;

public:
  auto tic() { this->BeginTime = ::std::chrono::high_resolution_clock::now(); }
  auto toc() { this->EndTime = ::std::chrono::high_resolution_clock::now(); }
  auto ellapsedTime() {
    return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
               this->EndTime - this->BeginTime)
        .count();
  }
};

template <class Container> auto incrementViaForLoop(Container &container) {
  for (auto i = 0U; i != container.size(); ++i) {
    container[i] = container[i] + 2U;
  }
}

template <class Container> auto incrementViaRangeLoop(Container &container) {
  for (auto &elem : container) {
    elem = elem + 2U;
  }
}

auto main(int argc, char **argv) -> int {
  auto sizeVector = 0;
  if (argc > 1) {
    sizeVector = 20000;
  }
  auto v8int = ::std::vector<::std::uint8_t>(sizeVector, 0);
  auto v32int = ::std::vector<::std::uint32_t>(sizeVector, 0);

  ::std::printf("sizeVector: %i\n", sizeVector);
  for (auto i = 0U; i != sizeVector; ++i) {
    v8int.emplace_back(::std::uint8_t{0U});
    v32int.emplace_back(::std::uint32_t{0U});
  }

  auto timer = Timer{};

  timer.tic();
  incrementViaForLoop(v8int);
  timer.toc();
  ::std::printf("uint8_t, for-loop: %lli\n", timer.ellapsedTime());

  timer.tic();
  incrementViaForLoop(v32int);
  timer.toc();
  ::std::printf("uint32_t, for-loop: %lli\n", timer.ellapsedTime());

  timer.tic();
  incrementViaRangeLoop(v8int);
  timer.toc();
  ::std::printf("uint8_t, range-for: %lli\n", timer.ellapsedTime());

  timer.tic();
  incrementViaRangeLoop(v32int);
  timer.toc();
  ::std::printf("uint32_t, range-for: %lli\n", timer.ellapsedTime());
}
